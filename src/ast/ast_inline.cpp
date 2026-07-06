#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_visitor.h"
#include "daScript/ast/ast_expressions.h"

namespace das {

    // ===== [inline] splicing, automatic block inlining, invoke devirtualization =====
    // Runs in the patch slot (Program::patchAnnotations -> patchInline), after infer and
    // buildAccessFlags, before lint and optimize. Splices are syntax-level: cloned callee
    // statements land in the caller, the pass reports astChanged, and the compiler restarts
    // infer, which re-resolves every ExprVar by name and legalizes types/r2v/temporaries.
    //
    // Three site kinds, two contracts:
    //  * [inline] calls (MUST): fail-closed. A callee shape the inliner can't splice is a
    //    compile error (annotation lint hook -> checkInlineShape, pointing at the
    //    declaration); a call site it can't host is a compile error reported here at the
    //    site. No size budgets, no decline paths. When a callee shape is bad the patch
    //    pass skips it SILENTLY and the lint hook reports it - both run on every compile,
    //    so a skip is never silent overall.
    //  * calls passing a block LITERAL argument (AUTO, optimized builds only): best-effort.
    //    The literal is the user's signal; nobody promised anything, so every gate -
    //    callee shape, unsafe in the body, recursion through the splice graph, private
    //    symbols, call position - declines SILENTLY (counted, logged under
    //    log_optimization). `options disable_auto_inline` (or the policy) turns it off.
    //  * invoke of a block literal (DEVIRT, same best-effort contract): an invoke whose
    //    block resolves to a same-function literal - directly or through a move-initialized,
    //    never-rewritten local (which is what an auto-spliced callee leaves behind) -
    //    splices the block body in place. Same-frame semantics make this a pure win: the
    //    body already reads the caller's locals directly.
    // The two halves converge over patch rounds: an auto splice moves the callee's invoke
    // next to the literal, the next round devirtualizes it, and any block-literal calls
    // inside the spliced body trigger further waves. Recursion through the combined graph
    // is declined up front, so the rounds terminate.
    //
    // Argument substitution is three-tier:
    //  (A) leaf args (constants; variable reads) substitute textually, no temp. A by-value
    //      param is a snapshot, so a leaf var the spliced body could write through another
    //      `var` by-ref param of the same call (or a global the callee's side effects could
    //      touch) binds a temp instead;
    //  (B) a pure (noSideEffects) non-leaf arg whose param is read at most once and not
    //      under a loop substitutes textually - evaluation can only become conditional
    //      (fewer evaluations of a pure expression), never repeated;
    //  (C) everything else binds a `let/var __inl<N>_arg_<param>` temp at the statement
    //      anchor in call-argument order: impure args evaluate exactly once in call order,
    //      multi-read params bind once, `var` by-value params ARE the mutable local copy.
    //
    // A call in a lazily- or repeatedly-evaluated position (&&/|| right side, ?: arms,
    // elif conditions, while conditions) that needs statements is handled by local
    // lowerings (while(C) -> while(true) if-break; elif -> blockified else; &&/||/?: ->
    // hoist + if-form). Each lowering changes the AST and converges over patch rounds.
    // Positions with no v1 lowering (?? right side, safe-navigation suffixes) error out.

    namespace {

        // ----- tiny callback walk (visitor without the boilerplate) -----

        template <typename TT>
        class LookupVisitor : public Visitor {
        public:
            LookupVisitor ( const TT & cb ) : callback(cb) {}
        protected:
            const TT & callback;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisitExpression ( Expression * expr ) override {
                Visitor::preVisitExpression(expr);
                callback(expr);
            }
        };

        template <typename TT>
        void lookupExpressions ( Expression * root, const TT & cb ) {
            LookupVisitor<TT> vis(cb);
            root->visit(vis);
        }

        // ----- callee shape -----

        class InlineShapeScan : public Visitor {
        public:
            InlineShapeScan ( bool blockLiteral = false ) : forBlockLiteral(blockLiteral) {}
            string reason;
            int returnCount = 0;
            Expression * lastTopLevelStmt = nullptr;
            Expression * misplacedReturn = nullptr;
            bool bad = false;
        protected:
            bool forBlockLiteral;
            int makeBlockDepth = 0;
            int loopDepth = 0;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            void flag ( const char * why ) { if ( !bad ) { bad = true; reason = why; } }
            virtual void preVisit ( ExprGoto * expr ) override { Visitor::preVisit(expr); flag("body contains goto"); }
            virtual void preVisit ( ExprLabel * expr ) override { Visitor::preVisit(expr); flag("body contains a label"); }
            virtual void preVisit ( ExprTryCatch * expr ) override { Visitor::preVisit(expr); flag("body contains try/recover"); }
            virtual void preVisit ( ExprYield * expr ) override { Visitor::preVisit(expr); flag("body contains yield"); }
            virtual void preVisit ( ExprFor * expr ) override { Visitor::preVisit(expr); loopDepth ++; }
            virtual ExpressionPtr visit ( ExprFor * expr ) override { loopDepth --; return Visitor::visit(expr); }
            virtual void preVisit ( ExprWhile * expr ) override { Visitor::preVisit(expr); loopDepth ++; }
            virtual ExpressionPtr visit ( ExprWhile * expr ) override { loopDepth --; return Visitor::visit(expr); }
            // splicing a block body inline dissolves the block boundary; a break/continue
            // not bound to a loop inside the body would re-bind to the invoke site's loop
            virtual void preVisit ( ExprBreak * expr ) override {
                Visitor::preVisit(expr);
                if ( forBlockLiteral && !makeBlockDepth && !loopDepth ) flag("body breaks out of the block");
            }
            virtual void preVisit ( ExprContinue * expr ) override {
                Visitor::preVisit(expr);
                if ( forBlockLiteral && !makeBlockDepth && !loopDepth ) flag("body continues out of the block");
            }
            virtual void preVisit ( ExprMakeBlock * expr ) override {
                Visitor::preVisit(expr);
                // a plain block literal stays in-frame and clones safely with the body;
                // lambda and local-function literals lower to generated functions during
                // infer, and cloning those post-infer is not safe
                if ( expr->isLambda || expr->isLocalFunction || !expr->capture.empty() ) {
                    flag("body contains a lambda literal");
                }
                makeBlockDepth ++;
            }
            virtual ExpressionPtr visit ( ExprMakeBlock * expr ) override {
                makeBlockDepth --;
                return Visitor::visit(expr);
            }
            virtual void preVisit ( ExprMakeGenerator * expr ) override { Visitor::preVisit(expr); flag("body contains a generator"); }
            virtual void preVisit ( ExprReturn * expr ) override {
                Visitor::preVisit(expr);
                if ( makeBlockDepth ) return;   // a return inside a block literal exits the block
                returnCount ++;
                if ( expr != lastTopLevelStmt ) misplacedReturn = expr;
            }
        };

        bool isPlainIdentifier ( const string & name ) {
            if ( name.empty() ) return false;
            return isalpha(uint8_t(name[0])) || name[0]=='_';
        }

        // ----- callee param read statistics (for tier B) -----

        struct ParamReadStats {
            das_hash_map<Variable *, int>   readCount;
            das_hash_set<Variable *>        readUnderLoop;
        };

        class ParamReadScan : public Visitor {
        public:
            ParamReadScan ( const vector<VariablePtr> & paramVars, ParamReadStats & st ) : stats(st) {
                for ( auto & arg : paramVars ) params.insert(arg);
            }
        protected:
            das_hash_set<Variable *> params;
            ParamReadStats & stats;
            int loopDepth = 0;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprFor * expr ) override { Visitor::preVisit(expr); loopDepth ++; }
            virtual ExpressionPtr visit ( ExprFor * expr ) override { loopDepth --; return Visitor::visit(expr); }
            virtual void preVisit ( ExprWhile * expr ) override { Visitor::preVisit(expr); loopDepth ++; }
            virtual ExpressionPtr visit ( ExprWhile * expr ) override { loopDepth --; return Visitor::visit(expr); }
            // a block literal's body may run any number of times - reads inside count as under-loop
            virtual void preVisit ( ExprMakeBlock * expr ) override { Visitor::preVisit(expr); loopDepth ++; }
            virtual ExpressionPtr visit ( ExprMakeBlock * expr ) override { loopDepth --; return Visitor::visit(expr); }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->variable && params.find(expr->variable)!=params.end() ) {
                    stats.readCount[expr->variable] ++;
                    if ( loopDepth ) stats.readUnderLoop.insert(expr->variable);
                }
            }
        };

        // ----- cross-module reference scan (splice gate) -----
        // a spliced body re-resolves its calls and globals in the DESTINATION module:
        // everything it references must be public and visible from there. generic
        // instances are judged by their origin (instances do not carry the private flag)

        class PrivateUseScan : public Visitor {
        public:
            PrivateUseScan ( Module * calleeModule, Module * destModule )
                : mod(calleeModule), dest(destModule) {}
            string privateSymbol;
        protected:
            Module * mod;
            Module * dest;
            void checkFunc ( Function * fn ) {
                if ( !fn || !privateSymbol.empty() ) return;
                auto origin = fn->fromGeneric ? fn->fromGeneric : fn;
                // instances are stamped private by instantiation, which keeps this gate
                // deliberately conservative: a body calling ANY generic instance stays
                // un-spliced across modules. Loosening it to origin-privateness re-fires
                // hundreds of linq_fold_common splices and destabilizes the fold macro's
                // shape assumptions - measure before widening
                if ( fn->privateFunction || origin->privateFunction ) {
                    if ( fn->module==mod || origin->module==mod ) {
                        privateSymbol = origin->name;
                        return;
                    }
                }
                if ( dest && origin->module && !dest->isVisibleDirectly(origin->module) ) {
                    privateSymbol = origin->name;
                }
            }
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprCall * expr ) override {
                Visitor::preVisit(expr);
                checkFunc(expr->func);
            }
            virtual void preVisit ( ExprOp1 * expr ) override {
                Visitor::preVisit(expr);
                checkFunc(expr->func);
            }
            virtual void preVisit ( ExprOp2 * expr ) override {
                Visitor::preVisit(expr);
                checkFunc(expr->func);
            }
            virtual void preVisit ( ExprOp3 * expr ) override {
                Visitor::preVisit(expr);
                checkFunc(expr->func);
            }
            virtual void preVisit ( ExprAddr * expr ) override {
                Visitor::preVisit(expr);
                checkFunc(expr->func);
            }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( !expr->variable || !privateSymbol.empty() ) return;
                if ( expr->variable->private_variable ) {
                    privateSymbol = expr->variable->name;
                } else if ( dest && expr->isGlobalVariable() && expr->variable->module
                    && !dest->isVisibleDirectly(expr->variable->module) ) {
                    privateSymbol = expr->variable->name;
                }
            }
        };

        // ----- cloned-body fixup: rename locals, substitute parameter reads -----

        struct ArgSub {
            Expression *    substitute = nullptr;   // tier A/B: clone this at every read
            string          tempName;               // tier C: read this temp instead
        };

        // the callee's local declarations, so reads can be renamed by name
        // (infer re-resolves every ExprVar by name; consistent renaming is all it takes)
        class LocalNameCollect : public Visitor {
        public:
            das_hash_map<string, string> * rename = nullptr;
            string prefix;
        protected:
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            void renameVar ( const string & name, const string & aka ) {
                if ( rename->find(name)==rename->end() ) (*rename)[name] = prefix + name;
                if ( !aka.empty() && rename->find(aka)==rename->end() ) (*rename)[aka] = prefix + name;
            }
            virtual void preVisitLet ( ExprLet * let, const VariablePtr & var, bool last ) override {
                Visitor::preVisitLet(let, var, last);
                renameVar(var->name, var->aka);
            }
            virtual void preVisit ( ExprFor * expr ) override {
                Visitor::preVisit(expr);
                for ( auto & var : expr->iteratorVariables ) renameVar(var->name, var->aka);
            }
            // block-literal arguments rename too: after the splice they sit in the caller's
            // scope chain, and an unrenamed argument could shadow a caller local (an error)
            virtual void preVisitBlockArgument ( ExprBlock * block, const VariablePtr & var, bool lastArg ) override {
                Visitor::preVisitBlockArgument(block, var, lastArg);
                renameVar(var->name, var->aka);
            }
        };

        // rewrites a cloned callee subtree for splicing:
        //  * parameter reads become the planned substitution or a temp read
        //  * local declarations and their reads get the __inl<N>_ prefix
        //  * r2v flags are cleared: a callee from another module is post-optimize
        //    (ref folding turned r2v wrappers into flags), and the flag would survive
        //    re-infer inconsistently - infer re-derives value reads from scratch
        class InlineBodyRewriter : public Visitor {
        public:
            das_hash_map<Variable *, ArgSub> * paramSub = nullptr;  // keyed by ORIGINAL callee param
            das_hash_map<string, string> * rename = nullptr;
            LineInfo tempAt;    // call site location for manufactured temp reads
        protected:
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual ExpressionPtr visit ( ExprVar * expr ) override {
                // cloned ExprVar nodes still point at the ORIGINAL callee variables
                // (ExprVar::clone copies the raw pointer) - param matching is exact
                if ( expr->variable ) {
                    auto it = paramSub->find(expr->variable);
                    if ( it != paramSub->end() ) {
                        if ( it->second.substitute ) return it->second.substitute->clone();
                        return new ExprVar(tempAt, it->second.tempName);
                    }
                }
                auto rit = rename->find(expr->name);
                if ( rit != rename->end() ) {
                    expr->name = rit->second;
                    expr->variable = nullptr;   // infer re-resolves by name
                }
                expr->r2v = false;
                return Visitor::visit(expr);
            }
            virtual ExpressionPtr visit ( ExprRef2Value * expr ) override {
                // a substituted value expression under an r2v wrapper leaves R2V(value);
                // drop the wrapper, the subexpression is already a value
                if ( expr->subexpr && expr->subexpr->type && !expr->subexpr->type->ref ) {
                    return expr->subexpr;
                }
                return Visitor::visit(expr);
            }
            virtual void preVisit ( ExprField * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisit ( ExprSafeField * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisit ( ExprAsVariant * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisit ( ExprSafeAsVariant * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisit ( ExprSwizzle * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisit ( ExprAt * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisit ( ExprSafeAt * expr ) override { Visitor::preVisit(expr); expr->r2v = false; }
            virtual void preVisitLet ( ExprLet * let, const VariablePtr & var, bool last ) override {
                Visitor::preVisitLet(let, var, last);
                auto rit = rename->find(var->name);
                if ( rit != rename->end() ) var->name = rit->second;
                if ( !var->aka.empty() ) {
                    auto ait = rename->find(var->aka);
                    if ( ait != rename->end() ) var->aka = ait->second;
                }
            }
            virtual void preVisit ( ExprFor * expr ) override {
                Visitor::preVisit(expr);
                for ( size_t i=0, is=expr->iterators.size(); i!=is; ++i ) {
                    auto rit = rename->find(expr->iterators[i]);
                    if ( rit != rename->end() ) expr->iterators[i] = rit->second;
                }
                for ( auto & var : expr->iteratorVariables ) {
                    auto rit = rename->find(var->name);
                    if ( rit != rename->end() ) var->name = rit->second;
                }
            }
            virtual void preVisitBlockArgument ( ExprBlock * block, const VariablePtr & var, bool lastArg ) override {
                Visitor::preVisitBlockArgument(block, var, lastArg);
                auto rit = rename->find(var->name);
                if ( rit != rename->end() ) var->name = rit->second;
                if ( !var->aka.empty() ) {
                    auto ait = rename->find(var->aka);
                    if ( ait != rename->end() ) var->aka = ait->second;
                }
            }
        };

        // replace one specific node (by identity) inside a statement
        class ReplaceNode : public Visitor {
        public:
            Expression * what = nullptr;
            ExpressionPtr with = nullptr;
            bool done = false;
        protected:
            virtual ExpressionPtr visitExpression ( Expression * expr ) override {
                if ( expr==what ) { done = true; return with; }
                return Visitor::visitExpression(expr);
            }
        };

        // ----- statement anchors (same scheme as the CSE prescan) -----

        struct StmtAnchor {
            ExprBlock * block = nullptr;
            int         index = -1;
        };

        enum class SiteKind {
            MustCall,   // call to an [inline] function: fail-closed contract, errors
            AutoCall,   // call with a block-literal argument: best-effort, silent declines
            Devirt      // invoke of a block literal (direct or let-bound): best-effort
        };

        struct PlannedSite {
            Expression * callLike = nullptr;    // ExprCall or ExprInvoke
            Expression * stmt = nullptr;
            StmtAnchor  anchor;
            SiteKind    kind = SiteKind::MustCall;
        };

        // annotations other than inert markers may carry call-site semantics (verifyCall,
        // transform, per-call codegen) that splicing the call away would bypass
        bool annotatedCallee ( Function * fn, string & why ) {
            for ( auto & ann : fn->annotations ) {
                if ( !ann->annotation ) continue;
                auto & nm = ann->annotation->name;
                if ( nm=="export" || nm=="unused_argument" ) continue;
                why = "annotated function [" + nm + "]";
                return true;
            }
            return false;
        }

        bool autoEligibleCall ( ExprCall * call ) {
            if ( !call->func || call->func->mustInline || call->func->builtIn ) return false;
            if ( !call->func->body || call->func->isTemplate ) return false;
            for ( auto & a : call->arguments ) {
                if ( a->rtti_isMakeBlock() ) return true;
            }
            return false;
        }

        // one walk per function: for every statement its (block, index) anchor, and
        // every splice site tagged with the statement that anchors it. a call in a
        // while/elif condition is tagged with the while/if statement itself; the
        // splice step lowers those constructs first when statements are needed.
        class InlineCollect : public Visitor {
        public:
            InlineCollect ( bool autoOn ) : autoEnabled(autoOn) {}
            vector<PlannedSite> sites;      // in visit order: within a block, increasing index
        protected:
            bool autoEnabled;
            vector<StmtAnchor> blockStack;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprBlock * blk ) override {
                Visitor::preVisit(blk);
                blockStack.push_back(StmtAnchor{blk, -1});
            }
            virtual ExpressionPtr visit ( ExprBlock * blk ) override {
                blockStack.pop_back();
                return Visitor::visit(blk);
            }
            virtual void preVisitBlockExpression ( ExprBlock * block, Expression * expr ) override {
                Visitor::preVisitBlockExpression(block, expr);
                if ( !blockStack.empty() && blockStack.back().block==block ) blockStack.back().index++;
            }
            void plan ( Expression * expr, SiteKind kind ) {
                // the anchoring statement is the innermost open block's CURRENT
                // statement - not the last statement any nested block visited
                // (an elif condition visits after the outer if's then-block)
                PlannedSite site;
                site.callLike = expr;
                site.kind = kind;
                if ( !blockStack.empty() && blockStack.back().index >= 0
                    && blockStack.back().index < int(blockStack.back().block->list.size()) ) {
                    site.anchor = blockStack.back();
                    site.stmt = site.anchor.block->list[site.anchor.index];
                }
                sites.push_back(site);
            }
            virtual void preVisit ( ExprCall * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->func && expr->func->mustInline ) {
                    plan(expr, SiteKind::MustCall);
                } else if ( autoEnabled && autoEligibleCall(expr) ) {
                    plan(expr, SiteKind::AutoCall);
                }
            }
            virtual void preVisit ( ExprInvoke * expr ) override {
                Visitor::preVisit(expr);
                if ( !autoEnabled || expr->isInvokeMethod || expr->arguments.empty() ) return;
                Expression * a0 = expr->arguments[0];
                if ( a0->rtti_isR2V() ) a0 = static_cast<ExprRef2Value *>(a0)->subexpr;
                if ( a0->rtti_isMakeBlock() || a0->rtti_isVar() ) plan(expr, SiteKind::Devirt);
            }
        };

        // let-bound block literals: a variable move-initialized from a block literal and
        // never REBOUND still holds that literal at every invoke. write flags are fresh
        // at patch time (buildAccessFlags runs right before patchAnnotations); an invoke
        // stamps a write on its non-const block argument, but invoking cannot rebind the
        // holder to a different literal, so arg0 occurrences stay clean for this purpose
        class BlockBindingScan : public Visitor {
        public:
            das_hash_map<Variable *, ExprMakeBlock *> binding;
            das_hash_set<Variable *> disq;
        protected:
            das_hash_set<Expression *> invokeArg0;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisitLet ( ExprLet * let, const VariablePtr & var, bool last ) override {
                Visitor::preVisitLet(let, var, last);
                if ( var->init && var->init->rtti_isMakeBlock() ) {
                    if ( binding.find(var)!=binding.end() ) disq.insert(var);  // paranoia: one binding only
                    binding[var] = static_cast<ExprMakeBlock *>(var->init);
                }
            }
            virtual void preVisit ( ExprInvoke * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->arguments.empty() ) return;
                Expression * a0 = expr->arguments[0];
                if ( a0->rtti_isR2V() ) a0 = static_cast<ExprRef2Value *>(a0)->subexpr;
                if ( a0->rtti_isVar() ) invokeArg0.insert(a0);
            }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->variable && expr->write
                    && invokeArg0.find(expr)==invokeArg0.end() ) disq.insert(expr->variable);
            }
        };

        // ----- eager-position and prefix analysis within one statement -----

        // children of `e` in evaluation order. lazyKind: 0 = evaluated eagerly exactly
        // once, 1 = lazy with a v1 lowering (&&, ||, ?:), 2 = lazy without one (??,
        // safe navigation). statement kinds list only their same-statement expressions
        // (an if statement lists its condition; nested blocks anchor their own statements)
        void childrenInEvalOrder ( Expression * e, vector<pair<Expression *,int>> & out ) {
            out.clear();
            if ( e->rtti_isOp3() ) {
                auto op3 = static_cast<ExprOp3 *>(e);
                out.emplace_back(op3->subexpr, 0);
                out.emplace_back(op3->left, 1);
                out.emplace_back(op3->right, 1);
            } else if ( e->rtti_isOp2() ) {
                // covers copy/move/clone too: destination address first, then the value
                auto op2 = static_cast<ExprOp2 *>(e);
                bool lazyRight = op2->op=="&&" || op2->op=="||";
                out.emplace_back(op2->left, 0);
                out.emplace_back(op2->right, lazyRight ? 1 : 0);
            } else if ( e->rtti_isNullCoalescing() ) {
                auto nc = static_cast<ExprNullCoalescing *>(e);
                out.emplace_back(nc->subexpr, 0);
                out.emplace_back(nc->defaultValue, 2);
            } else if ( e->rtti_isSafeField() ) {
                out.emplace_back(static_cast<ExprSafeField *>(e)->value, 0);
            } else if ( e->rtti_isSafeAt() ) {
                auto sa = static_cast<ExprSafeAt *>(e);
                out.emplace_back(sa->subexpr, 0);
                out.emplace_back(sa->index, 2);
            } else if ( e->rtti_isOp1() ) {
                out.emplace_back(static_cast<ExprOp1 *>(e)->subexpr, 0);
            } else if ( e->rtti_isR2V() ) {
                out.emplace_back(static_cast<ExprRef2Value *>(e)->subexpr, 0);
            } else if ( e->rtti_isCall() ) {
                auto c = static_cast<ExprCall *>(e);
                for ( auto & a : c->arguments ) out.emplace_back(a, 0);
            } else if ( e->rtti_isInvoke() ) {
                auto inv = static_cast<ExprInvoke *>(e);
                for ( auto & a : inv->arguments ) out.emplace_back(a, 0);
            } else if ( e->rtti_isStringBuilder() ) {
                auto sb = static_cast<ExprStringBuilder *>(e);
                for ( auto & a : sb->elements ) out.emplace_back(a, 0);
            } else if ( e->rtti_isReturn() ) {
                auto r = static_cast<ExprReturn *>(e);
                if ( r->subexpr ) out.emplace_back(r->subexpr, 0);
            } else if ( e->rtti_isLet() ) {
                auto let = static_cast<ExprLet *>(e);
                for ( auto & v : let->variables ) {
                    if ( v->init ) out.emplace_back(v->init, 0);
                }
            } else if ( e->rtti_isIfThenElse() ) {
                out.emplace_back(static_cast<ExprIfThenElse *>(e)->cond, 0);
            } else if ( e->rtti_isFor() ) {
                auto f = static_cast<ExprFor *>(e);
                for ( auto & s : f->sources ) out.emplace_back(s, 0);
            } else if ( e->rtti_isWith() ) {
                out.emplace_back(static_cast<ExprWith *>(e)->with, 0);
            } else if ( e->rtti_isField() ) {
                out.emplace_back(static_cast<ExprField *>(e)->value, 0);
            } else if ( e->rtti_isAt() ) {
                auto at = static_cast<ExprAt *>(e);
                out.emplace_back(at->subexpr, 0);
                out.emplace_back(at->index, 0);
            } else if ( e->rtti_isCast() ) {
                out.emplace_back(static_cast<ExprCast *>(e)->subexpr, 0);
            } else if ( e->rtti_isUnsafe() ) {
                out.emplace_back(static_cast<ExprUnsafe *>(e)->body, 0);
            }
        }

        // conservative purity for tier-B substitution and prefix hoisting. the
        // per-expression noSideEffects flags are computed by checkSideEffects()
        // during optimize - at patch time they are stale or unset - but function
        // level sideEffectFlags ARE fresh (buildAccessFlags runs right before the
        // patch slot), so derive purity from the tree + callee flags directly.
        // a global READ counts as impure: reordering it across a global write is
        // observable, and both tier B and prefix hoisting move evaluation
        bool inlinePure ( Expression * e ) {
            if ( !e ) return true;
            if ( e->rtti_isConstant() ) return true;
            if ( e->rtti_isMakeBlock() ) return true;   // making a block writes nothing (and
                                                        // hoisting one would copy a non-copyable)
            if ( e->rtti_isTypeDecl() ) return true;    // type<...> witness: a compile-time tag
            if ( e->rtti_isUnsafe() ) return inlinePure(static_cast<ExprUnsafe *>(e)->body);
            if ( e->rtti_isVar() ) return !static_cast<ExprVar *>(e)->isGlobalVariable();
            if ( e->rtti_isR2V() ) return inlinePure(static_cast<ExprRef2Value *>(e)->subexpr);
            if ( e->rtti_isField() ) return inlinePure(static_cast<ExprField *>(e)->value);
            if ( e->rtti_isSafeField() ) return inlinePure(static_cast<ExprSafeField *>(e)->value);
            if ( e->rtti_isAsVariant() ) return inlinePure(static_cast<ExprAsVariant *>(e)->value);
            if ( e->rtti_isSafeAsVariant() ) return inlinePure(static_cast<ExprSafeAsVariant *>(e)->value);
            if ( e->rtti_isSwizzle() ) return inlinePure(static_cast<ExprSwizzle *>(e)->value);
            if ( e->rtti_isCast() ) return inlinePure(static_cast<ExprCast *>(e)->subexpr);
            if ( e->rtti_isAt() ) {
                auto at = static_cast<ExprAt *>(e);
                return inlinePure(at->subexpr) && inlinePure(at->index);
            }
            if ( e->rtti_isSafeAt() ) {
                auto at = static_cast<ExprSafeAt *>(e);
                return inlinePure(at->subexpr) && inlinePure(at->index);
            }
            if ( e->rtti_isNullCoalescing() ) {
                auto nc = static_cast<ExprNullCoalescing *>(e);
                return inlinePure(nc->subexpr) && inlinePure(nc->defaultValue);
            }
            const uint32_t impureMask =
                  uint32_t(SideEffects::userScenario)
                | uint32_t(SideEffects::modifyExternal)
                | uint32_t(SideEffects::modifyArgument)
                | uint32_t(SideEffects::accessGlobal)
                | uint32_t(SideEffects::invoke);
            if ( e->rtti_isOp1() ) {
                auto op = static_cast<ExprOp1 *>(e);
                if ( op->func && (op->func->sideEffectFlags & impureMask) ) return false;
                return inlinePure(op->subexpr);
            }
            if ( e->rtti_isOp2() ) {
                auto op = static_cast<ExprOp2 *>(e);
                if ( op->func && (op->func->sideEffectFlags & impureMask) ) return false;
                return inlinePure(op->left) && inlinePure(op->right);
            }
            if ( e->rtti_isOp3() ) {
                auto op = static_cast<ExprOp3 *>(e);
                if ( op->func && (op->func->sideEffectFlags & impureMask) ) return false;
                return inlinePure(op->subexpr) && inlinePure(op->left) && inlinePure(op->right);
            }
            if ( e->rtti_isCall() ) {
                auto c = static_cast<ExprCall *>(e);
                if ( !c->func || (c->func->sideEffectFlags & impureMask) ) return false;
                for ( auto & a : c->arguments ) {
                    if ( !inlinePure(a) ) return false;
                }
                return true;
            }
            return false;   // unrecognized - conservatively impure
        }

        // a callee that writes nothing (no var by-ref params, no external state, no
        // globals - accessGlobal does not distinguish reads from writes - no invokes)
        // cannot invalidate anything an argument expression read - textual
        // substitution is then order-safe for any pure argument
        bool calleeWriteFree ( Function * fn ) {
            const uint32_t writeMask =
                  uint32_t(SideEffects::userScenario)
                | uint32_t(SideEffects::modifyExternal)
                | uint32_t(SideEffects::modifyArgument)
                | uint32_t(SideEffects::accessGlobal)
                | uint32_t(SideEffects::invoke);
            return (fn->sideEffectFlags & writeMask)==0;
        }

        // the arguments and parameters of one splice site: a direct call binds the whole
        // argument list, an invoke binds arguments[1..] against the block's parameters
        struct SiteArgs {
            const vector<ExpressionPtr> *  args = nullptr;
            size_t                         ofs = 0;
            const vector<VariablePtr> *    params = nullptr;
            size_t count () const { return params->size(); }
            Expression * arg ( size_t i ) const { return (*args)[ofs+i]; }
            const VariablePtr & param ( size_t i ) const { return (*params)[i]; }
        };

        // for a callee that DOES write: a substituted argument may only read storage
        // the spliced body provably cannot touch - plain local by-value variables that
        // are not passed by mutable reference in this very call and whose address was
        // never taken. no field / index / deref reads at all (they may reach heap or
        // aliased storage). constants and operations over such leaves are fine
        bool argReadsOnlyPrivateLocals ( Expression * e, const SiteArgs & sa ) {
            if ( !e ) return true;
            if ( e->rtti_isConstant() ) return true;
            if ( e->rtti_isVar() ) {
                auto v = static_cast<ExprVar *>(e);
                if ( !v->variable ) return false;
                if ( v->isGlobalVariable() ) return false;
                if ( v->variable->access_ref ) return false;    // address taken somewhere
                auto vt = v->variable->type;
                if ( vt && (vt->ref || vt->isRefType()) ) return false;
                for ( size_t oi=0, ois=sa.count(); oi!=ois; ++oi ) {
                    auto & OP = sa.param(oi);
                    bool oRef = OP->type->ref || OP->type->isRefType();
                    if ( !oRef || OP->type->constant ) continue;
                    Expression * oleaf = sa.arg(oi);
                    if ( oleaf->rtti_isR2V() ) oleaf = static_cast<ExprRef2Value *>(oleaf)->subexpr;
                    if ( oleaf->rtti_isVar() && static_cast<ExprVar *>(oleaf)->variable==v->variable ) return false;
                }
                return true;
            }
            if ( e->rtti_isR2V() ) return argReadsOnlyPrivateLocals(static_cast<ExprRef2Value *>(e)->subexpr, sa);
            if ( e->rtti_isCast() ) return argReadsOnlyPrivateLocals(static_cast<ExprCast *>(e)->subexpr, sa);
            if ( e->rtti_isOp1() ) return argReadsOnlyPrivateLocals(static_cast<ExprOp1 *>(e)->subexpr, sa);
            if ( e->rtti_isOp2() ) {
                auto op = static_cast<ExprOp2 *>(e);
                return argReadsOnlyPrivateLocals(op->left, sa)
                    && argReadsOnlyPrivateLocals(op->right, sa);
            }
            if ( e->rtti_isOp3() ) {
                auto op = static_cast<ExprOp3 *>(e);
                return argReadsOnlyPrivateLocals(op->subexpr, sa)
                    && argReadsOnlyPrivateLocals(op->left, sa)
                    && argReadsOnlyPrivateLocals(op->right, sa);
            }
            if ( e->rtti_isCall() ) {
                auto c = static_cast<ExprCall *>(e);
                for ( auto & a : c->arguments ) {
                    if ( !argReadsOnlyPrivateLocals(a, sa) ) return false;
                }
                return true;
            }
            return false;
        }

        bool exprContains ( Expression * root, Expression * what ) {
            if ( root==what ) return true;
            vector<pair<Expression *,int>> kids;
            childrenInEvalOrder(root, kids);
            for ( auto & k : kids ) {
                if ( k.first && exprContains(k.first, what) ) return true;
            }
            return false;
        }

        enum class SitePosition { Eager, Lazy, NotFound, Unsupported };

        struct PathScan {
            vector<Expression *> lazyOps;   // lazy ops on the path, outermost LAST (pushed on unwind)
        };

        SitePosition findPath ( Expression * root, Expression * call, PathScan & scan ) {
            if ( root==call ) return SitePosition::Eager;
            vector<pair<Expression *,int>> kids;
            childrenInEvalOrder(root, kids);
            for ( auto & k : kids ) {
                if ( !k.first ) continue;
                if ( !exprContains(k.first, call) ) continue;
                auto sub = findPath(k.first, call, scan);
                if ( sub==SitePosition::NotFound || sub==SitePosition::Unsupported ) return sub;
                if ( k.second==2 ) return SitePosition::Unsupported;
                if ( k.second==1 ) {
                    scan.lazyOps.push_back(root);
                    return SitePosition::Lazy;
                }
                return sub;
            }
            return SitePosition::NotFound;
        }

        // maximal impure subexpressions evaluated strictly before `call` within `root`,
        // in evaluation order. hoisting them (whole, internal laziness intact) keeps the
        // spliced arg temps from jumping ahead of earlier side effects
        void collectImpurePrefix ( Expression * root, Expression * call, vector<Expression *> & prefix ) {
            if ( root==call ) return;
            vector<pair<Expression *,int>> kids;
            childrenInEvalOrder(root, kids);
            for ( auto & k : kids ) {
                if ( !k.first ) continue;
                if ( exprContains(k.first, call) ) {
                    collectImpurePrefix(k.first, call, prefix);
                    return;
                }
                if ( !inlinePure(k.first) ) prefix.push_back(k.first);
            }
        }

        // manufactured `let/var name [&] = init` (or an uninitialized declaration)
        ExprLet * makeTemp ( const LineInfo & at, const string & name, Expression * init,
                             bool isConst, bool isRef, bool viaMove ) {
            auto var = new Variable();
            var->name = name;
            var->at = at;
            var->generated = true;
            var->type = new TypeDecl(Type::autoinfer);
            var->type->constant = isConst;
            // autoinfer inherits constness from the init; a mutable temp initialized
            // from a constant must strip it (the `-const` operator) or writes fail
            var->type->removeConstant = !isConst;
            var->type->ref = isRef;
            var->init = init;
            var->init_via_move = viaMove;
            auto let = new ExprLet();
            let->at = at;
            let->atInit = init ? init->at : at;
            let->variables.push_back(var);
            return let;
        }

        ExprLet * makeUninitDecl ( const LineInfo & at, const string & name, const TypeDecl * type ) {
            auto var = new Variable();
            var->name = name;
            var->at = at;
            var->generated = true;
            var->type = new TypeDecl(*type);
            var->type->constant = false;
            var->type->ref = false;
            var->type->safeWhenUninitialized = true;    // assigned before any read by construction
            auto let = new ExprLet();
            let->at = at;
            let->variables.push_back(var);
            return let;
        }

    } // anonymous namespace

    // ----- the [inline] shape contract -----

    bool checkInlineShape ( Function * fn, string & err ) {
        if ( fn->isTemplate ) return true;      // instances are checked instead
        if ( fn->builtIn || !fn->body ) { err = "[inline] requires a function with a das body"; return false; }
        if ( !fn->body->rtti_isBlock() ) { err = "[inline] requires a block body"; return false; }
        if ( fn->generator ) { err = "[inline] does not support generators"; return false; }
        if ( fn->lambda ) { err = "[inline] does not support lambdas"; return false; }
        if ( fn->isClassMethod || fn->classParent ) { err = "[inline] does not support class methods"; return false; }
        if ( fn->isCustomProperty || fn->propertyFunction ) { err = "[inline] does not support property functions"; return false; }
        // a generic instance is named `origin`<hash> - judge by the origin's name.
        // operator overloads (punctuation names) are called through ExprOp nodes,
        // which the splicer does not visit, so they can't honor the contract
        const string & plainName = fn->fromGeneric ? fn->fromGeneric->name : fn->name;
        if ( !isPlainIdentifier(plainName) ) { err = "[inline] does not support operator overloads ('" + plainName + "')"; return false; }
        if ( fn->result && !fn->result->isVoid() ) {
            if ( fn->result->ref || fn->result->isRefType() ) {
                err = "[inline] result must be by-value (or void)";
                return false;
            }
        }
        for ( auto & arg : fn->arguments ) {
            if ( !arg->type ) continue;
            if ( arg->type->temporary ) { err = "[inline] does not support temporary (#) parameter '" + arg->name + "'"; return false; }
            if ( arg->type->implicit ) { err = "[inline] does not support implicit parameter '" + arg->name + "'"; return false; }
            // a smart-pointer argument temp would need inscope/move discipline the
            // splicer does not manufacture (strict_smart_pointers rejects the copy)
            if ( arg->type->smartPtr ) { err = "[inline] does not support smart-pointer parameter '" + arg->name + "'"; return false; }
        }
        if ( fn->result && fn->result->smartPtr ) { err = "[inline] does not support a smart-pointer result"; return false; }
        auto body = static_cast<ExprBlock *>(fn->body);
        InlineShapeScan scan;
        scan.lastTopLevelStmt = body->list.empty() ? nullptr : body->list.back();
        fn->body->visit(scan);
        if ( scan.bad ) { err = "[inline] " + scan.reason; return false; }
        if ( scan.misplacedReturn ) {
            err = "[inline] requires a single-exit body - return is only allowed as the last statement";
            return false;
        }
        bool isVoid = !fn->result || fn->result->isVoid();
        if ( !isVoid && scan.returnCount!=1 ) {
            err = "[inline] requires a single-exit body with one trailing return";
            return false;
        }
        return true;
    }

    // true when `fn` is reachable from its own body through direct calls to [inline]
    // functions - splicing such a cycle would never terminate
    static bool inlineGraphReaches ( Function * target, Function * cur, das_hash_set<Function *> & visited ) {
        if ( !cur->body ) return false;
        bool found = false;
        lookupExpressions(cur->body, [&](Expression * expr) {
            if ( found || !expr->rtti_isCall() ) return;
            auto call = static_cast<ExprCall *>(expr);
            if ( !call->func || !call->func->mustInline ) return;
            if ( call->func==target ) { found = true; return; }
            if ( visited.insert(call->func).second ) {
                if ( inlineGraphReaches(target, call->func, visited) ) found = true;
            }
        });
        return found;
    }

    bool checkInlineRecursion ( Function * fn, string & err ) {
        if ( fn->isTemplate || !fn->body ) return true;
        das_hash_set<Function *> visited;
        if ( inlineGraphReaches(fn, fn, visited) ) {
            err = "[inline] function is recursive through the inline graph";
            return false;
        }
        return true;
    }

    // ----- best-effort shape gates (auto inlining and devirtualization decline, never error) -----

    namespace {

        // a block literal the devirtualizer can splice in place: a plain in-frame block
        // with a single-exit body and a by-value (or void) result. splicing dissolves the
        // block boundary, so a break/continue not bound to a loop inside the body is out
        bool checkDevirtShape ( ExprMakeBlock * mkb, string & why ) {
            if ( mkb->isLambda || mkb->isLocalFunction || !mkb->capture.empty() ) { why = "lambda literal"; return false; }
            if ( !mkb->block || !mkb->block->rtti_isBlock() ) { why = "no block body"; return false; }
            auto blk = static_cast<ExprBlock *>(mkb->block);
            bool isVoid = !blk->returnType || blk->returnType->isVoid();
            if ( !isVoid && (blk->returnType->ref || blk->returnType->isRefType()) ) {
                why = "result is not by-value";
                return false;
            }
            for ( auto & arg : blk->arguments ) {
                if ( !arg->type ) { why = "unresolved parameter"; return false; }
                if ( arg->type->temporary ) { why = "temporary (#) parameter"; return false; }
                if ( arg->type->implicit ) { why = "implicit parameter"; return false; }
                if ( arg->type->smartPtr ) { why = "smart-pointer parameter"; return false; }
            }
            if ( blk->returnType && blk->returnType->smartPtr ) { why = "smart-pointer result"; return false; }
            InlineShapeScan scan(true);
            scan.lastTopLevelStmt = blk->list.empty() ? nullptr : blk->list.back();
            blk->visit(scan);
            if ( scan.bad ) { why = scan.reason; return false; }
            if ( scan.misplacedReturn ) { why = "multiple exits"; return false; }
            if ( !isVoid && scan.returnCount!=1 ) { why = "multiple exits"; return false; }
            return true;
        }

        // recursion over the whole splice graph - [inline] calls and auto-eligible
        // block-literal calls alike - would re-manufacture eligible sites every round
        bool spliceGraphReaches ( Function * target, Function * cur, das_hash_set<Function *> & visited ) {
            if ( !cur->body ) return false;
            bool found = false;
            lookupExpressions(cur->body, [&](Expression * expr) {
                if ( found || !expr->rtti_isCall() ) return;
                auto call = static_cast<ExprCall *>(expr);
                if ( !call->func ) return;
                if ( !call->func->mustInline && !autoEligibleCall(call) ) return;
                if ( call->func==target ) { found = true; return; }
                if ( visited.insert(call->func).second ) {
                    if ( spliceGraphReaches(target, call->func, visited) ) found = true;
                }
            });
            return found;
        }

    } // anonymous namespace

    // ----- the patch pass -----

    namespace {

        struct InlinePatch {
            Program * program = nullptr;
            TextWriter * logs = nullptr;
            bool logOpt = false;
            bool mustEnabled = true;
            bool autoEnabled = false;
            bool changed = false;
            int inlined = 0;        // [inline] sites
            int inlinedAuto = 0;    // auto block-literal call sites
            int devirted = 0;       // invoke-of-literal sites
            int declined = 0;       // best-effort sites the pass passed on
            das_hash_map<ExprBlock *, ParamReadStats> statsCache;
            das_hash_map<Function *, bool> shapeCache;
            das_hash_map<Function *, pair<bool,string>> autoOkCache;
            das_hash_map<ExprMakeBlock *, pair<bool,string>> devirtShapeCache;
            das_hash_map<Function *, string> privateUseCache;

            bool calleeShapeOk ( Function * fn ) {
                auto it = shapeCache.find(fn);
                if ( it != shapeCache.end() ) return it->second;
                string err;
                bool ok = checkInlineShape(fn, err) && checkInlineRecursion(fn, err);
                shapeCache[fn] = ok;
                return ok;
            }

            // best-effort callee gate: [inline]'s shape contract, plus no unsafe in the
            // body (a spliced unsafe re-checks against the CALLER module's permissions),
            // plus no recursion through the combined splice graph
            bool autoCalleeOk ( Function * fn, string & why ) {
                auto it = autoOkCache.find(fn);
                if ( it != autoOkCache.end() ) { why = it->second.second; return it->second.first; }
                bool ok = true;
                if ( !checkInlineShape(fn, why) ) {
                    ok = false;
                } else if ( fn->unsafeOperation || fn->unsafeDeref || fn->hasUnsafe ) {
                    // hasUnsafe is stamped by infer and survives foldUnsafe: a spliced
                    // unsafe body would re-check against the caller's module, wrapper-less
                    ok = false;
                    why = "unsafe operation";
                } else if ( annotatedCallee(fn, why) ) {
                    ok = false;     // an annotation may carry call-site semantics
                                    // (verifyCall & co) that a splice would bypass
                } else {
                    // a type<...> witness naming the generic's own alias (type<TT>) stays
                    // symbolic in the instance body and cannot re-resolve after a splice
                    bool aliasWitness = false;
                    lookupExpressions(fn->body, [&](Expression * expr) {
                        if ( aliasWitness || !expr->rtti_isTypeDecl() ) return;
                        auto td = static_cast<ExprTypeDecl *>(expr);
                        if ( td->typeexpr && td->typeexpr->isAutoOrAlias() ) aliasWitness = true;
                    });
                    if ( aliasWitness ) {
                        ok = false;
                        why = "body carries a generic type witness";
                    } else {
                        das_hash_set<Function *> visited;
                        if ( spliceGraphReaches(fn, fn, visited) ) {
                            ok = false;
                            why = "recursive through the inline graph";
                        }
                    }
                }
                autoOkCache[fn] = pair<bool,string>(ok, why);
                return ok;
            }

            bool devirtShapeOk ( ExprMakeBlock * mkb, string & why ) {
                auto it = devirtShapeCache.find(mkb);
                if ( it != devirtShapeCache.end() ) { why = it->second.second; return it->second.first; }
                bool ok = checkDevirtShape(mkb, why);
                devirtShapeCache[mkb] = pair<bool,string>(ok, why);
                return ok;
            }

            const ParamReadStats & paramStats ( ExprBlock * body, const vector<VariablePtr> & params ) {
                auto it = statsCache.find(body);
                if ( it != statsCache.end() ) return it->second;
                auto & st = statsCache[body];
                ParamReadScan scan(params, st);
                body->visit(scan);
                return st;
            }

            const string & privateUse ( Function * fn, Module * originModule ) {
                auto it = privateUseCache.find(fn);
                if ( it != privateUseCache.end() ) return it->second;
                PrivateUseScan scan(originModule, program->thisModule.get());
                fn->body->visit(scan);
                return privateUseCache[fn] = scan.privateSymbol;
            }

            // next free __inl counter in this function; names are function-scoped and
            // later rounds keep splicing into the same function, so continue the sequence
            int nextInlineId ( Function * fn ) {
                int mx = 0;
                auto consider = [&]( const string & name ) {
                    if ( name.compare(0, 5, "__inl")==0 ) {
                        int id = atoi(name.c_str()+5);
                        if ( id >= mx ) mx = id + 1;
                    }
                };
                lookupExpressions(fn->body, [&](Expression * expr) {
                    if ( expr->rtti_isLet() ) {
                        auto let = static_cast<ExprLet *>(expr);
                        for ( auto & v : let->variables ) consider(v->name);
                    } else if ( expr->rtti_isFor() ) {
                        auto f = static_cast<ExprFor *>(expr);
                        for ( auto & v : f->iteratorVariables ) consider(v->name);
                    }
                });
                return mx;
            }

            void error ( const string & what, const LineInfo & at ) {
                program->error(what, "", "", at, CompilationError::invalid_annotation);
            }

            // a MUST site that can't splice fails the compile; a best-effort site
            // declines silently (counted, logged under log_optimization)
            void siteFail ( const PlannedSite & site, const string & what, const LineInfo & at ) {
                if ( site.kind==SiteKind::MustCall ) {
                    error(what, at);
                } else {
                    decline(site, what, at);
                }
            }

            void decline ( const PlannedSite & site, const string & why, const LineInfo & at ) {
                declined ++;
                if ( logOpt && logs ) {
                    *logs << (site.kind==SiteKind::Devirt ? "DEVIRT DECLINED at " : "AUTO-INLINE DECLINED at ")
                          << at.describe() << ": " << why << "\n";
                }
            }

            void completeSite ( const PlannedSite & site, Function * caller, const string & subjName ) {
                switch ( site.kind ) {
                    case SiteKind::MustCall: inlined ++; break;
                    case SiteKind::AutoCall: inlinedAuto ++; break;
                    case SiteKind::Devirt:   devirted ++; break;
                }
                if ( logOpt && logs ) {
                    const char * verb = site.kind==SiteKind::MustCall ? "INLINE "
                        : site.kind==SiteKind::AutoCall ? "AUTO-INLINE " : "DEVIRT ";
                    *logs << verb << subjName << " into " << caller->getMangledName()
                          << " at " << site.callLike->at.describe() << "\n";
                }
                changed = true;
            }

            void processFunction ( Function * fn );
        };

        void InlinePatch::processFunction ( Function * fn ) {
            InlineCollect collect(autoEnabled);
            fn->body->visit(collect);
            if ( collect.sites.empty() ) return;
            // let-bound block literals this function's invokes may resolve to
            das_hash_map<Variable *, ExprMakeBlock *> bindings;
            if ( autoEnabled ) {
                BlockBindingScan bscan;
                fn->body->visit(bscan);
                for ( auto & kv : bscan.binding ) {
                    if ( bscan.disq.find(kv.first)==bscan.disq.end() ) bindings[kv.first] = kv.second;
                }
            }
            int inlineId = nextInlineId(fn);
            // a splice shifts the indices of later statements in the same block
            das_hash_map<ExprBlock *, int> indexShift;
            for ( auto & site : collect.sites ) {
                auto callLike = site.callLike;
                if ( site.kind==SiteKind::MustCall && !mustEnabled ) continue;
                // ----- resolve the splice subject -----
                Function * calleeFn = nullptr;          // MustCall / AutoCall
                ExprMakeBlock * literal = nullptr;      // Devirt
                string subjName;
                if ( site.kind==SiteKind::Devirt ) {
                    auto inv = static_cast<ExprInvoke *>(callLike);
                    Expression * a0 = inv->arguments[0];
                    if ( a0->rtti_isR2V() ) a0 = static_cast<ExprRef2Value *>(a0)->subexpr;
                    if ( a0->rtti_isMakeBlock() ) {
                        literal = static_cast<ExprMakeBlock *>(a0);
                    } else if ( a0->rtti_isVar() ) {
                        auto v = static_cast<ExprVar *>(a0);
                        if ( v->variable ) {
                            auto bit = bindings.find(v->variable);
                            if ( bit!=bindings.end() ) literal = bit->second;
                        }
                    }
                    if ( !literal ) continue;   // not a traceable block literal
                    subjName = "block";
                } else {
                    calleeFn = static_cast<ExprCall *>(callLike)->func;
                    subjName = calleeFn->name;
                }
                if ( !site.stmt || !site.anchor.block ) {
                    siteFail(site, "can't inline " + subjName + " here: the call is outside a function statement", callLike->at);
                    continue;
                }
                int anchorIndex = site.anchor.index + indexShift[site.anchor.block];
                // an earlier action this round may have rewritten this site's statement
                // (var+if lowering), moved its subtree into a hoist temp, or detached it
                // by cloning (arg temps, grafts). a site whose call is no longer live at
                // its recorded statement is skipped; the next patch round collects the
                // moved/cloned call at its new home. liveness mirrors exactly what the
                // processing below can reach: eval-order positions, a while condition,
                // or an elif condition still in unblockified chain form
                if ( anchorIndex < 0 || anchorIndex >= int(site.anchor.block->list.size())
                    || site.anchor.block->list[anchorIndex] != site.stmt ) {
                    continue;
                }
                bool siteLive = exprContains(site.stmt, callLike);
                if ( !siteLive && site.stmt->rtti_isWhile() ) {
                    siteLive = exprContains(static_cast<ExprWhile *>(site.stmt)->cond, callLike);
                }
                if ( !siteLive && site.stmt->rtti_isIfThenElse() ) {
                    auto lite = static_cast<ExprIfThenElse *>(site.stmt);
                    while ( lite->if_false && lite->if_false->rtti_isIfThenElse() ) {
                        auto inner = static_cast<ExprIfThenElse *>(lite->if_false);
                        if ( exprContains(inner->cond, callLike) ) { siteLive = true; break; }
                        lite = inner;
                    }
                }
                if ( !siteLive ) continue;
                // ----- subject shape gates -----
                ExprBlock * body = nullptr;
                TypeDecl * subjResult = nullptr;    // null = void result
                SiteArgs sa;
                if ( site.kind==SiteKind::Devirt ) {
                    string why;
                    if ( !devirtShapeOk(literal, why) ) { decline(site, why, callLike->at); continue; }
                    auto blk = static_cast<ExprBlock *>(literal->block);
                    auto inv = static_cast<ExprInvoke *>(callLike);
                    if ( inv->arguments.size() != blk->arguments.size()+1 ) { decline(site, "argument count mismatch", callLike->at); continue; }
                    body = blk;
                    if ( blk->returnType && !blk->returnType->isVoid() ) subjResult = blk->returnType;
                    sa.args = &inv->arguments; sa.ofs = 1; sa.params = &blk->arguments;
                } else {
                    auto call = static_cast<ExprCall *>(callLike);
                    if ( site.kind==SiteKind::MustCall ) {
                        if ( !calleeShapeOk(calleeFn) ) continue;   // lint reports at the declaration
                    } else {
                        string why;
                        if ( !autoCalleeOk(calleeFn, why) ) { decline(site, subjName + ": " + why, callLike->at); continue; }
                    }
                    if ( call->arguments.size() != calleeFn->arguments.size() ) continue; // not fully inferred - defensive
                    // a generic instance lives in the CALLER's module - judge its home
                    // (and the reachability of its references) by the generic's origin
                    Module * originModule = calleeFn->fromGeneric
                        ? calleeFn->fromGeneric->module : calleeFn->module;
                    if ( originModule != program->thisModule.get() ) {
                        auto & priv = privateUse(calleeFn, originModule);
                        if ( !priv.empty() ) {
                            siteFail(site, "can't inline " + subjName + " across modules: body uses private symbol '" + priv + "'", callLike->at);
                            continue;
                        }
                    }
                    body = static_cast<ExprBlock *>(calleeFn->body);
                    if ( calleeFn->result && !calleeFn->result->isVoid() ) subjResult = calleeFn->result;
                    sa.args = &call->arguments; sa.ofs = 0; sa.params = &calleeFn->arguments;
                }
                // ----- classify arguments -----
                auto & stats = paramStats(body, *sa.params);
                bool isVoid = subjResult==nullptr;
                bool exprBody = body->list.size()==1 && body->list.back()->rtti_isReturn();
                bool writeFree = calleeFn ? calleeWriteFree(calleeFn) : false;  // a block body is judged unknown
                das_hash_map<Variable *, ArgSub> paramSub;
                vector<ExpressionPtr> temps;
                for ( size_t ai=0, ais=sa.count(); ai!=ais; ++ai ) {
                    Expression * A = sa.arg(ai);
                    auto & P = sa.param(ai);
                    ArgSub sub;
                    bool byRefParam = P->type->ref || P->type->isRefType();
                    bool varParam = !P->type->constant;
                    Expression * leafA = A;
                    if ( leafA->rtti_isR2V() ) leafA = static_cast<ExprRef2Value *>(leafA)->subexpr;
                    bool leafConst = leafA->rtti_isConstant();
                    bool leafVar = leafA->rtti_isVar();
                    auto makeArgTemp = [&]( Expression * init, bool cnst, bool ref, bool viaMove ) {
                        string tname = "__inl" + to_string(inlineId) + "_arg_" + P->name;
                        temps.push_back(makeTemp(callLike->at, tname, init, cnst, ref, viaMove));
                        sub.tempName = tname;
                    };
                    if ( leafA->rtti_isTypeDecl() ) {
                        // type<...> witness: a compile-time tag - a temp would "use" it
                        sub.substitute = leafA;
                        paramSub[P] = sub;
                        continue;
                    }
                    if ( byRefParam ) {
                        if ( leafVar ) {
                            sub.substitute = leafA;             // same aliasing as the call itself
                        } else if ( leafA->rtti_isMakeBlock() ) {
                            // a block literal read once outside loops substitutes textually,
                            // keeping shapes a holder can't reproduce (temporary-typed block
                            // parameters do not survive a `var <-` binding). multi-read and
                            // under-loop literals bind a holder; devirtualization takes over
                            int reads = 0;
                            auto rit = stats.readCount.find(P);
                            if ( rit != stats.readCount.end() ) reads = rit->second;
                            bool underLoop = stats.readUnderLoop.find(P)!=stats.readUnderLoop.end();
                            if ( reads<=1 && !underLoop ) {
                                sub.substitute = leafA;
                            } else {
                                makeArgTemp(A->clone(), false, false, true);
                            }
                        } else if ( A->type && A->type->ref ) {
                            // lvalue chain (field/index): bind a reference once, like the call did
                            auto init = A->clone();
                            init->alwaysSafe = true;            // generated binding to real storage
                            makeArgTemp(init, !varParam, true, false);
                        } else {
                            // rvalue into a ref param: materialize the value. constness
                            // follows the param (a var-ref param - e.g. a consumed iterator -
                            // needs a mutable holder), and a block always binds `var`: a const
                            // holder const-propagates into the invoke, rejecting the block's
                            // own var parameters
                            bool nonCopyable = A->type && !A->type->canCopy();
                            bool blockValue = A->type && A->type->baseType==Type::tBlock;
                            makeArgTemp(A->clone(), !varParam && !blockValue, false, nonCopyable);
                        }
                    } else if ( varParam ) {
                        // a mutable by-value param IS a local copy
                        makeArgTemp(A->clone(), false, false, false);
                    } else if ( leafConst ) {
                        sub.substitute = leafA;
                    } else if ( leafVar ) {
                        auto av = static_cast<ExprVar *>(leafA);
                        // snapshot hazard: the spliced body could write the same storage
                        // through a `var` by-ref param of this very call, or through globals
                        bool hazard = false;
                        if ( av->variable ) {
                            for ( size_t oi=0; oi!=ais; ++oi ) {
                                if ( oi==ai ) continue;
                                auto & OP = sa.param(oi);
                                bool oRef = OP->type->ref || OP->type->isRefType();
                                if ( !oRef || OP->type->constant ) continue;
                                Expression * oleaf = sa.arg(oi);
                                if ( oleaf->rtti_isR2V() ) oleaf = static_cast<ExprRef2Value *>(oleaf)->subexpr;
                                if ( oleaf->rtti_isVar() && static_cast<ExprVar *>(oleaf)->variable==av->variable ) {
                                    hazard = true;
                                    break;
                                }
                            }
                            if ( !hazard && (av->isGlobalVariable() || av->variable->access_ref) ) {
                                // a global, or a local whose address escaped: the spliced
                                // body's writes could reach it, breaking snapshot semantics
                                hazard = !writeFree;
                            }
                        }
                        if ( hazard ) {
                            makeArgTemp(A->clone(), true, false, false);
                        } else {
                            sub.substitute = leafA;
                        }
                    } else {
                        // tier B: pure, read at most once, never under a loop
                        int reads = 0;
                        auto rit = stats.readCount.find(P);
                        if ( rit != stats.readCount.end() ) reads = rit->second;
                        bool underLoop = stats.readUnderLoop.find(P)!=stats.readUnderLoop.end();
                        bool orderSafe = writeFree || argReadsOnlyPrivateLocals(A, sa);
                        if ( reads<=1 && !underLoop && inlinePure(A) && orderSafe ) {
                            sub.substitute = A;
                        } else {
                            makeArgTemp(A->clone(), true, false, false);
                        }
                    }
                    paramSub[P] = sub;
                }
                bool needStatements = !temps.empty() || !exprBody;
                if ( !needStatements ) {
                    // ----- pure graft: no statements, no anchors, legal in any position -----
                    das_hash_map<string, string> rename;    // expression bodies declare no locals
                    InlineBodyRewriter rewriter;
                    rewriter.paramSub = &paramSub;
                    rewriter.rename = &rename;
                    rewriter.tempAt = callLike->at;
                    auto ret = static_cast<ExprReturn *>(body->list.back());
                    ExpressionPtr callReplacement = nullptr;
                    if ( ret->subexpr ) {
                        callReplacement = ret->subexpr->clone()->visit(rewriter);
                    }
                    if ( site.stmt==callLike ) {
                        auto & list = site.anchor.block->list;
                        if ( callReplacement ) {
                            list[anchorIndex] = callReplacement;
                        } else {
                            list.erase(list.begin()+anchorIndex);
                            indexShift[site.anchor.block] -= 1;
                        }
                    } else {
                        ReplaceNode rn;
                        rn.what = callLike;
                        rn.with = callReplacement;
                        if ( !callReplacement ) {
                            siteFail(site, "can't inline void " + subjName + " here: the call is not a statement", callLike->at);
                            continue;
                        }
                        auto & slot = site.anchor.block->list[anchorIndex];
                        slot = slot->visit(rn);
                        if ( !rn.done ) {
                            error("internal error: inlined call not found in its statement", callLike->at);
                            continue;
                        }
                    }
                    completeSite(site, fn, subjName);
                    inlineId ++;
                    continue;
                }
                // ----- statements needed: check the position, lower if necessary -----
                if ( site.stmt->rtti_isWhile() ) {
                    auto wh = static_cast<ExprWhile *>(site.stmt);
                    if ( exprContains(wh->cond, callLike) && wh->body->rtti_isBlock() ) {
                        // while(C) -> while(true) { if (!(C)) break; ... } - the condition
                        // becomes a statement-anchored expression, next round splices there
                        auto brkBlock = new ExprBlock();
                        brkBlock->at = wh->cond->at;
                        brkBlock->list.push_back(new ExprBreak(wh->cond->at));
                        auto guard = new ExprIfThenElse(wh->cond->at,
                            new ExprOp1(wh->cond->at, "!", wh->cond), brkBlock, nullptr);
                        auto oldBody = static_cast<ExprBlock *>(wh->body);
                        oldBody->list.insert(oldBody->list.begin(), guard);
                        wh->cond = new ExprConstBool(wh->cond->at, true);
                        changed = true;
                        continue;
                    }
                }
                if ( site.stmt->rtti_isIfThenElse() ) {
                    // call in an elif condition: blockify that else so the inner if
                    // becomes an anchorable statement of its own
                    auto ite = static_cast<ExprIfThenElse *>(site.stmt);
                    bool lowered = false;
                    while ( ite->if_false && ite->if_false->rtti_isIfThenElse() ) {
                        auto inner = static_cast<ExprIfThenElse *>(ite->if_false);
                        if ( exprContains(inner->cond, callLike) || exprContains(ite->if_false, callLike) ) {
                            auto blk = new ExprBlock();
                            blk->at = inner->at;
                            blk->list.push_back(ite->if_false);
                            ite->if_false = blk;
                            lowered = true;
                            break;
                        }
                        ite = inner;
                    }
                    if ( lowered ) {
                        changed = true;
                        continue;
                    }
                }
                PathScan path;
                auto pos = findPath(site.stmt, callLike, path);
                if ( pos==SitePosition::NotFound ) {
                    siteFail(site, "can't inline " + subjName + " here: unsupported call position", callLike->at);
                    continue;
                }
                if ( pos==SitePosition::Unsupported ) {
                    siteFail(site, "can't inline " + subjName + " inside ?? or a safe-navigation suffix - hoist the call into its own statement", callLike->at);
                    continue;
                }
                if ( pos==SitePosition::Lazy ) {
                    auto lazy = path.lazyOps.back();    // outermost lazy op on the path
                    // when the lazy op is the whole init of a single GENERATED temp (a
                    // hoist from a previous round), rewrite it to var + if form in place.
                    // a USER declaration never takes this branch - replacing it would drop
                    // its metadata (constness, aka, ref-ness); it hoists to a fresh temp
                    // instead, and the next round rewrites that temp
                    Variable * rootVar = nullptr;
                    if ( site.stmt->rtti_isLet() ) {
                        auto let = static_cast<ExprLet *>(site.stmt);
                        if ( let->variables.size()==1 && let->variables[0]->init==lazy
                            && let->variables[0]->generated ) {
                            rootVar = let->variables[0];
                        }
                    }
                    auto & list = site.anchor.block->list;
                    if ( !rootVar ) {
                        string tname = "__inl" + to_string(inlineId) + "_low";
                        inlineId ++;
                        // a non-const temp: a `var p = <temp>` consumer of pointer type
                        // rejects initialization from a const reference
                        auto hoist = makeTemp(callLike->at, tname, lazy, false, false, false);
                        ReplaceNode rn;
                        rn.what = lazy;
                        rn.with = new ExprVar(callLike->at, tname);
                        list[anchorIndex] = list[anchorIndex]->visit(rn);
                        if ( !rn.done ) {
                            error("internal error: lazy operator not found in its statement", callLike->at);
                            continue;
                        }
                        list.insert(list.begin()+anchorIndex, hoist);
                        indexShift[site.anchor.block] += 1;
                        changed = true;
                        continue;
                    }
                    if ( !lazy->type ) {
                        siteFail(site, "can't inline " + subjName + " here: missing type on the lazy operator", callLike->at);
                        continue;
                    }
                    vector<ExpressionPtr> replacement;
                    replacement.push_back(makeUninitDecl(site.stmt->at, rootVar->name, lazy->type));
                    auto readT = [&]() { return new ExprVar(site.stmt->at, rootVar->name); };
                    if ( lazy->rtti_isOp3() ) {
                        auto op3 = static_cast<ExprOp3 *>(lazy);
                        auto thenBlk = new ExprBlock();
                        thenBlk->at = op3->at;
                        thenBlk->list.push_back(new ExprCopy(op3->at, readT(), op3->left));
                        auto elseBlk = new ExprBlock();
                        elseBlk->at = op3->at;
                        elseBlk->list.push_back(new ExprCopy(op3->at, readT(), op3->right));
                        replacement.push_back(new ExprIfThenElse(op3->at, op3->subexpr, thenBlk, elseBlk));
                    } else if ( lazy->rtti_isOp2() ) {
                        auto op2 = static_cast<ExprOp2 *>(lazy);
                        replacement.push_back(new ExprCopy(op2->at, readT(), op2->left));
                        auto thenBlk = new ExprBlock();
                        thenBlk->at = op2->at;
                        thenBlk->list.push_back(new ExprCopy(op2->at, readT(), op2->right));
                        ExpressionPtr cond = readT();
                        if ( op2->op=="||" ) cond = new ExprOp1(op2->at, "!", cond);
                        replacement.push_back(new ExprIfThenElse(op2->at, cond, thenBlk, nullptr));
                    } else {
                        siteFail(site, "can't inline " + subjName + " here: unsupported lazy operator", callLike->at);
                        continue;
                    }
                    list.erase(list.begin()+anchorIndex);
                    list.insert(list.begin()+anchorIndex, replacement.begin(), replacement.end());
                    indexShift[site.anchor.block] += int(replacement.size()) - 1;
                    changed = true;
                    continue;
                }
                // ----- eager position: hoist the impure prefix, splice temps and body -----
                vector<Expression *> prefix;
                collectImpurePrefix(site.stmt, callLike, prefix);
                vector<ExpressionPtr> splice;
                bool prefixFailed = false;
                int preIdx = 0;
                for ( auto pe : prefix ) {
                    if ( pe->type && pe->type->isVoid() ) {
                        // a void expression can only BE the statement, and then it has no prefix
                        siteFail(site, "can't inline " + subjName + " here: void expression in the evaluation prefix", callLike->at);
                        prefixFailed = true;
                        break;
                    }
                    string tname = "__inl" + to_string(inlineId) + "_pre" + to_string(preIdx++);
                    // non-const temps throughout: the hoisted expression was a non-const
                    // rvalue (or keeps its lvalue constness via the reference binding), and
                    // a const temp read would no longer match var pointer params downstream
                    if ( pe->type && pe->type->ref ) {
                        // lvalue: bind a reference once - evaluation order and identity
                        // both survive (writes through the temp land in the original place)
                        pe->alwaysSafe = true;          // generated binding to real storage
                        splice.push_back(makeTemp(pe->at, tname, pe, pe->type->constant, true, false));
                    } else if ( pe->type && !pe->type->canCopy() ) {
                        splice.push_back(makeTemp(pe->at, tname, pe, false, false, true));  // move the rvalue
                    } else {
                        splice.push_back(makeTemp(pe->at, tname, pe, false, false, false));
                    }
                    ReplaceNode rn;
                    rn.what = pe;
                    rn.with = new ExprVar(pe->at, tname);
                    auto & slot = site.anchor.block->list[anchorIndex];
                    slot = slot->visit(rn);
                    if ( !rn.done ) {
                        error("internal error: prefix expression not found in its statement", callLike->at);
                        prefixFailed = true;
                        break;
                    }
                }
                if ( prefixFailed ) continue;
                for ( auto & t : temps ) splice.push_back(t);
                // body
                das_hash_map<string, string> rename;
                LocalNameCollect names;
                names.rename = &rename;
                // renamed locals live in the _l_ sub-namespace so a callee local named
                // `res` (or `arg_x`, `pre0`, `low`) can never collide with the
                // manufactured _res/_arg_*/_pre*/_low temps of the same site
                names.prefix = "__inl" + to_string(inlineId) + "_l_";
                body->visit(names);
                InlineBodyRewriter rewriter;
                rewriter.paramSub = &paramSub;
                rewriter.rename = &rename;
                rewriter.tempAt = callLike->at;
                ExpressionPtr callReplacement = nullptr;
                if ( exprBody ) {
                    auto ret = static_cast<ExprReturn *>(body->list.back());
                    if ( ret->subexpr ) {
                        callReplacement = ret->subexpr->clone()->visit(rewriter);
                    }
                } else {
                    auto bodyClone = static_cast<ExprBlock *>(body->clone());
                    if ( site.kind==SiteKind::Devirt ) {
                        // the literal's parameters became substitutions and its result
                        // becomes the result temp: the spliced copy is a plain scope block
                        bodyClone->arguments.clear();
                        bodyClone->annotations.clear();
                        bodyClone->returnType = nullptr;
                        bodyClone->isClosure = false;
                        bodyClone->isLambdaBlock = false;
                        bodyClone->hasReturn = false;
                        bodyClone->copyOnReturn = false;
                        bodyClone->moveOnReturn = false;
                    }
                    ExpressionPtr trailing = nullptr;
                    if ( !bodyClone->list.empty() && bodyClone->list.back()->rtti_isReturn() ) {
                        trailing = bodyClone->list.back();
                        bodyClone->list.pop_back();
                    }
                    if ( !isVoid ) {
                        string resName = "__inl" + to_string(inlineId) + "_res";
                        splice.push_back(makeUninitDecl(callLike->at, resName, subjResult));
                        auto ret = static_cast<ExprReturn *>(trailing);
                        bodyClone->list.push_back(new ExprCopy(ret->at,
                            new ExprVar(ret->at, resName), ret->subexpr));
                        callReplacement = new ExprVar(callLike->at, resName);
                    }
                    splice.push_back(bodyClone->visit(rewriter));
                }
                auto & list = site.anchor.block->list;
                list.insert(list.begin()+anchorIndex, splice.begin(), splice.end());
                indexShift[site.anchor.block] += int(splice.size());
                int stmtIndex = anchorIndex + int(splice.size());
                if ( list[stmtIndex]==callLike ) {
                    // the call IS the statement
                    if ( callReplacement ) {
                        list[stmtIndex] = callReplacement;
                    } else {
                        list.erase(list.begin()+stmtIndex);
                        indexShift[site.anchor.block] -= 1;
                    }
                } else {
                    ReplaceNode rn;
                    rn.what = callLike;
                    rn.with = callReplacement;
                    list[stmtIndex] = list[stmtIndex]->visit(rn);
                    if ( !rn.done ) {
                        error("internal error: inlined call not found in its statement", callLike->at);
                        continue;
                    }
                }
                completeSite(site, fn, subjName);
                inlineId ++;
            }
        }

        // DFS postorder over the splice graph inside this module, [inline] functions
        // first: a chain f -> g -> h splices already-inlined bodies in a single round
        void orderInlineFunctions ( Module * thisMod, Function * fn, bool autoOn,
                vector<Function *> & order, das_hash_set<Function *> & seen ) {
            if ( !fn->body || fn->isTemplate || fn->stub ) return;
            if ( fn->module != thisMod ) return;
            if ( !seen.insert(fn).second ) return;
            lookupExpressions(fn->body, [&](Expression * expr) {
                if ( expr->rtti_isCall() ) {
                    auto call = static_cast<ExprCall *>(expr);
                    if ( !call->func ) return;
                    if ( call->func->mustInline || (autoOn && autoEligibleCall(call)) ) {
                        orderInlineFunctions(thisMod, call->func, autoOn, order, seen);
                    }
                }
            });
            order.push_back(fn);
        }

        // ----- return canonicalization (pre-pass) -----

        // optimized builds canonicalize early-exit shapes before candidates are evaluated:
        //  (1) tail-else synthesis: `if (c) { ...; return }` followed by a tail moves the
        //      tail into a synthesized else arm (what CondFolding does for nested blocks
        //      at optimize time; here it also covers the function's top block);
        //  (2) `if (c) return a; else return b;` folds to `return c ? a : b`.
        // together they turn early-exit bodies into the single-trailing-return shape the
        // inliner requires. new nodes are untyped: the pass reports astChanged and the
        // restarted infer legalizes them, the same protocol as a splice. the optimize-time
        // CondFolding copy stays - it serves compiles this pre-pass never sees (auto
        // inlining off) and macro-generated post-infer shapes.
        class ReturnCanonicalization : public Visitor {
        public:
            bool changed = false;
        protected:
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            // extract `return ...` from an if arm: a naked return (an inner fold leaves one
            // behind in an elif chain), or a block holding exactly one return. blocks with
            // a finally section never qualify - the fold would drop it. CMRES makes stay
            // behind: the make-local protocol doesn't survive under an Op3 arm
            static ExprReturn * armReturn ( Expression * arm ) {
                ExprReturn * ret = nullptr;
                if ( arm->rtti_isReturn() ) {
                    ret = static_cast<ExprReturn *>(arm);
                } else if ( arm->rtti_isBlock() ) {
                    auto blk = static_cast<ExprBlock *>(arm);
                    if ( blk->list.size()==1 && blk->finalList.empty() && blk->list.back()->rtti_isReturn() ) {
                        ret = static_cast<ExprReturn *>(blk->list.back());
                    }
                }
                if ( ret && ret->subexpr && ret->subexpr->rtti_isMakeLocal() ) ret = nullptr;
                return ret;
            }
            // the restarted infer expects parser shapes, where an if arm is a block. an
            // inner fold leaves a naked return as the arm of an elif chain; when the outer
            // if does not itself fold away, re-block the arm
            static void reblockArm ( ExpressionPtr & arm ) {
                if ( arm && arm->rtti_isReturn() ) {
                    auto blk = new ExprBlock();
                    blk->at = arm->at;
                    blk->list.push_back(arm);
                    arm = blk;
                }
            }
            virtual ExpressionPtr visit ( ExprIfThenElse * expr ) override {
                if ( expr->if_false && !expr->isStatic && !expr->doNotFold ) {
                    ExprReturn * lr = armReturn(expr->if_true);
                    ExprReturn * rr = armReturn(expr->if_false);
                    if ( lr && rr && lr->moveSemantics==rr->moveSemantics ) {
                        // a same-walk inner fold leaves untyped subexprs; decline those -
                        // the arm folds on the next patch round, once infer has typed it.
                        // return coercion is per-arm but ternary arms must match EACH OTHER,
                        // and the merged arm loses per-arm coercions: `return derived?` vs
                        // `return base?` stays an if, and so does `return null` (the null
                        // literal to typed pointer coercion doesn't survive under an Op3 arm)
                        if ( lr->subexpr && rr->subexpr
                            && lr->subexpr->type && rr->subexpr->type
                            && !lr->subexpr->type->isRef() && !rr->subexpr->type->isRef()
                            && !lr->subexpr->type->isVoid()
                            && !lr->subexpr->type->isVoidPointer() && !rr->subexpr->type->isVoidPointer()
                            && lr->subexpr->type->isSameType(*rr->subexpr->type, RefMatters::no, ConstMatters::no, TemporaryMatters::yes) ) {
                            auto ternary = new ExprOp3(expr->at, "?", expr->cond, lr->subexpr, rr->subexpr);
                            auto ret = new ExprReturn(expr->at, ternary);
                            ret->moveSemantics = lr->moveSemantics;
                            changed = true;
                            return ret;
                        } else if ( !lr->subexpr && !rr->subexpr && inlinePure(expr->cond) ) {
                            // both arms are bare returns and evaluating the cond does nothing
                            changed = true;
                            return lr;
                        }
                    }
                }
                reblockArm(expr->if_true);
                reblockArm(expr->if_false);
                return Visitor::visit(expr);
            }
            virtual ExpressionPtr visit ( ExprBlock * block ) override {
                // a finally section references block locals BY NAME; nesting tail
                // declarations under a synthesized else would hide them from it when
                // infer re-resolves (the optimize-time copy of this transform survives
                // only because post-infer references are by pointer)
                if ( !block->finalList.empty() ) return Visitor::visit(block);
                // tail-else synthesis, reversed order so one walk handles a whole batch
                bool any = false;
                for ( int i = int(block->list.size()) - 2; i>=0; i-- ) {
                    auto expr = block->list[i];
                    if ( !expr->rtti_isIfThenElse() ) continue;
                    auto ite = static_cast<ExprIfThenElse *>(expr);
                    if ( ite->if_false || ite->isStatic || ite->doNotFold || !ite->if_true->rtti_isBlock() ) continue;
                    auto tb = static_cast<ExprBlock *>(ite->if_true);
                    if ( tb->list.empty() ) continue;
                    auto lastE = tb->list.back();
                    if ( lastE->rtti_isReturn() || lastE->rtti_isBreak() || lastE->rtti_isContinue() ) {
                        auto fb = new ExprBlock();
                        fb->at = block->list[i+1]->at;
                        fb->list.assign(block->list.begin()+i+1, block->list.end());
                        ite->if_false = fb;
                        block->list.resize(i+1);
                        any = true;
                    }
                }
                if ( any ) changed = true;
                return Visitor::visit(block);
            }
        };

        bool canonicalizeReturns ( Function * fn ) {
            if ( !fn->body || !fn->body->rtti_isBlock() ) return false;
            if ( fn->generator || fn->isTemplate ) return false;
            // [inline] bodies stay untouched: their shape contract is fail-closed, and a
            // multi-exit [inline] callee must be the same compile error at every -O level
            if ( fn->mustInline ) return false;
            // goto can target a label in a tail this pass would move into an else arm; the
            // feature is rare enough that any use opts the whole function out
            bool hasGotoOrLabel = false;
            lookupExpressions(fn->body, [&](Expression * e) {
                if ( e->rtti_isGoto() || e->rtti_isLabel() ) hasGotoOrLabel = true;
            });
            if ( hasGotoOrLabel ) return false;
            bool any = false;
            for ( int round = 0; round!=16; ++round ) {   // converges in 2-3; the cap is paranoia
                ReturnCanonicalization pass;
                fn->body = fn->body->visit(pass);
                if ( !pass.changed ) break;
                any = true;
            }
            return any;
        }

    } // anonymous namespace

    bool Program::patchInline() {
        bool mustEnabled = !options.getBoolOption("disable_inline", policies.disable_inline);
        // best-effort inlining is an optimization: it stays out of unoptimized builds
        bool autoEnabled = getOptimize()
            && !options.getBoolOption("disable_auto_inline", policies.disable_auto_inline);
        // canonicalize early-exit shapes ahead of candidacy: single exit is an inline shape
        // requirement, and the rewrite must settle (re-infer) before anything splices on
        // top of it. gated with auto inlining rather than bare optimization:
        // `disable_auto_inline` is the one knob that promises "no patch-slot reshaping"
        // to shape-pinning tests and macros
        if ( autoEnabled && !failed() ) {
            bool canon = false;
            thisModule->functions.foreach([&](auto fn) {
                canon |= canonicalizeReturns(fn);
            });
            if ( canon ) return true;
        }
        // cheap gate: any [inline] function visible at all?
        bool anyInline = false;
        if ( mustEnabled ) {
            library.foreach([&](Module * mod) -> bool {
                if ( !anyInline ) {
                    mod->functions.find_first([&](auto fn) {
                        if ( fn->mustInline ) { anyInline = true; return true; }
                        return false;
                    });
                }
                return true;
            }, "*");
        }
        if ( !anyInline && !autoEnabled ) return false;
        InlinePatch patch;
        patch.program = this;
        patch.logs = daScriptEnvironment::getBound()->g_compilerLog;
        patch.logOpt = options.getBoolOption("log_optimization", policies.log_optimization);
        patch.mustEnabled = mustEnabled && anyInline;
        patch.autoEnabled = autoEnabled;
        vector<Function *> order;
        das_hash_set<Function *> seen;
        thisModule->functions.foreach([&](auto fn) {
            if ( fn->mustInline ) orderInlineFunctions(thisModule.get(), fn, autoEnabled, order, seen);
        });
        thisModule->functions.foreach([&](auto fn) {
            orderInlineFunctions(thisModule.get(), fn, autoEnabled, order, seen);
        });
        for ( auto fn : order ) {
            patch.processFunction(fn);
            if ( failed() ) break;
        }
        if ( patch.logOpt && patch.logs
            && (patch.inlined || patch.inlinedAuto || patch.devirted || patch.declined) ) {
            *patch.logs << "INLINE: " << patch.inlined << " must + " << patch.inlinedAuto
                        << " auto + " << patch.devirted << " devirt site(s), "
                        << patch.declined << " declined in module " << thisModule->name << "\n";
        }
        return patch.changed;
    }

}
