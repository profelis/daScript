#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_visitor.h"
#include "daScript/ast/ast_expressions.h"

namespace das {

    // ===== [inline] splicing =====
    // Runs in the patch slot (Program::patchAnnotations -> patchInline), after infer and
    // buildAccessFlags, before lint and optimize. Splices are syntax-level: cloned callee
    // statements land in the caller, the pass reports astChanged, and the compiler restarts
    // infer, which re-resolves every ExprVar by name and legalizes types/r2v/temporaries.
    //
    // The contract is fail-closed: [inline] is a promise, not a hint. A callee shape the
    // inliner can't splice is a compile error (annotation lint hook -> checkInlineShape,
    // pointing at the declaration); a call site it can't host is a compile error reported
    // here at the site. The pass has no size budgets and no decline paths. When a callee
    // shape is bad the patch pass skips it SILENTLY and the lint hook reports it - both
    // run on every compile, so a skip is never silent overall.
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
            string reason;
            int returnCount = 0;
            Expression * lastTopLevelStmt = nullptr;
            Expression * misplacedReturn = nullptr;
            bool bad = false;
        protected:
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            void flag ( const char * why ) { if ( !bad ) { bad = true; reason = why; } }
            virtual void preVisit ( ExprGoto * expr ) override { Visitor::preVisit(expr); flag("body contains goto"); }
            virtual void preVisit ( ExprLabel * expr ) override { Visitor::preVisit(expr); flag("body contains a label"); }
            virtual void preVisit ( ExprTryCatch * expr ) override { Visitor::preVisit(expr); flag("body contains try/recover"); }
            virtual void preVisit ( ExprYield * expr ) override { Visitor::preVisit(expr); flag("body contains yield"); }
            virtual void preVisit ( ExprMakeBlock * expr ) override { Visitor::preVisit(expr); flag("body contains a block, lambda, or generator literal"); }
            virtual void preVisit ( ExprMakeGenerator * expr ) override { Visitor::preVisit(expr); flag("body contains a generator"); }
            virtual void preVisit ( ExprReturn * expr ) override {
                Visitor::preVisit(expr);
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
            ParamReadScan ( Function * fn, ParamReadStats & st ) : stats(st) {
                for ( auto & arg : fn->arguments ) params.insert(arg);
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
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->variable && params.find(expr->variable)!=params.end() ) {
                    stats.readCount[expr->variable] ++;
                    if ( loopDepth ) stats.readUnderLoop.insert(expr->variable);
                }
            }
        };

        // ----- private-symbol scan (cross-module splice gate) -----

        class PrivateUseScan : public Visitor {
        public:
            PrivateUseScan ( Module * calleeModule ) : mod(calleeModule) {}
            string privateSymbol;
        protected:
            Module * mod;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprCall * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->func && expr->func->privateFunction && expr->func->module==mod && privateSymbol.empty() ) {
                    privateSymbol = expr->func->name;
                }
            }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->variable && expr->variable->private_variable && privateSymbol.empty() ) {
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

        struct PlannedSite {
            ExprCall *  call = nullptr;
            Expression * stmt = nullptr;
            StmtAnchor  anchor;
        };

        // one walk per function: for every statement its (block, index) anchor, and
        // every mustInline call site tagged with the statement that anchors it. a call
        // in a while/elif condition is tagged with the while/if statement itself; the
        // splice step lowers those constructs first when statements are needed.
        class InlineCollect : public Visitor {
        public:
            vector<PlannedSite> sites;      // in visit order: within a block, increasing index
        protected:
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
            virtual void preVisit ( ExprCall * expr ) override {
                Visitor::preVisit(expr);
                if ( expr->func && expr->func->mustInline ) {
                    // the anchoring statement is the innermost open block's CURRENT
                    // statement - not the last statement any nested block visited
                    // (an elif condition visits after the outer if's then-block)
                    PlannedSite site;
                    site.call = expr;
                    if ( !blockStack.empty() && blockStack.back().index >= 0
                        && blockStack.back().index < int(blockStack.back().block->list.size()) ) {
                        site.anchor = blockStack.back();
                        site.stmt = site.anchor.block->list[site.anchor.index];
                    }
                    sites.push_back(site);
                }
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

        // for a callee that DOES write: a substituted argument may only read storage
        // the spliced body provably cannot touch - plain local by-value variables that
        // are not passed by mutable reference in this very call and whose address was
        // never taken. no field / index / deref reads at all (they may reach heap or
        // aliased storage). constants and operations over such leaves are fine
        bool argReadsOnlyPrivateLocals ( Expression * e, ExprCall * call, Function * callee ) {
            if ( !e ) return true;
            if ( e->rtti_isConstant() ) return true;
            if ( e->rtti_isVar() ) {
                auto v = static_cast<ExprVar *>(e);
                if ( !v->variable ) return false;
                if ( v->isGlobalVariable() ) return false;
                if ( v->variable->access_ref ) return false;    // address taken somewhere
                auto vt = v->variable->type;
                if ( vt && (vt->ref || vt->isRefType()) ) return false;
                for ( size_t oi=0, ois=call->arguments.size(); oi!=ois; ++oi ) {
                    auto & OP = callee->arguments[oi];
                    bool oRef = OP->type->ref || OP->type->isRefType();
                    if ( !oRef || OP->type->constant ) continue;
                    Expression * oleaf = call->arguments[oi];
                    if ( oleaf->rtti_isR2V() ) oleaf = static_cast<ExprRef2Value *>(oleaf)->subexpr;
                    if ( oleaf->rtti_isVar() && static_cast<ExprVar *>(oleaf)->variable==v->variable ) return false;
                }
                return true;
            }
            if ( e->rtti_isR2V() ) return argReadsOnlyPrivateLocals(static_cast<ExprRef2Value *>(e)->subexpr, call, callee);
            if ( e->rtti_isCast() ) return argReadsOnlyPrivateLocals(static_cast<ExprCast *>(e)->subexpr, call, callee);
            if ( e->rtti_isOp1() ) return argReadsOnlyPrivateLocals(static_cast<ExprOp1 *>(e)->subexpr, call, callee);
            if ( e->rtti_isOp2() ) {
                auto op = static_cast<ExprOp2 *>(e);
                return argReadsOnlyPrivateLocals(op->left, call, callee)
                    && argReadsOnlyPrivateLocals(op->right, call, callee);
            }
            if ( e->rtti_isOp3() ) {
                auto op = static_cast<ExprOp3 *>(e);
                return argReadsOnlyPrivateLocals(op->subexpr, call, callee)
                    && argReadsOnlyPrivateLocals(op->left, call, callee)
                    && argReadsOnlyPrivateLocals(op->right, call, callee);
            }
            if ( e->rtti_isCall() ) {
                auto c = static_cast<ExprCall *>(e);
                for ( auto & a : c->arguments ) {
                    if ( !argReadsOnlyPrivateLocals(a, call, callee) ) return false;
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

        SitePosition findPath ( Expression * root, ExprCall * call, PathScan & scan ) {
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
        void collectImpurePrefix ( Expression * root, ExprCall * call, vector<Expression *> & prefix ) {
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
        }
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

    // ----- the patch pass -----

    namespace {

        struct InlinePatch {
            Program * program = nullptr;
            TextWriter * logs = nullptr;
            bool logOpt = false;
            bool changed = false;
            int inlined = 0;
            das_hash_map<Function *, ParamReadStats> statsCache;
            das_hash_map<Function *, bool> shapeCache;
            das_hash_map<Function *, string> privateUseCache;

            bool calleeShapeOk ( Function * fn ) {
                auto it = shapeCache.find(fn);
                if ( it != shapeCache.end() ) return it->second;
                string err;
                bool ok = checkInlineShape(fn, err) && checkInlineRecursion(fn, err);
                shapeCache[fn] = ok;
                return ok;
            }

            const ParamReadStats & paramStats ( Function * fn ) {
                auto it = statsCache.find(fn);
                if ( it != statsCache.end() ) return it->second;
                auto & st = statsCache[fn];
                ParamReadScan scan(fn, st);
                fn->body->visit(scan);
                return st;
            }

            const string & privateUse ( Function * fn ) {
                auto it = privateUseCache.find(fn);
                if ( it != privateUseCache.end() ) return it->second;
                PrivateUseScan scan(fn->module);
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

            void logSite ( Function * caller, ExprCall * call ) {
                if ( logOpt && logs ) {
                    *logs << "INLINE " << call->func->getMangledName() << " into "
                          << caller->getMangledName() << " at " << call->at.describe() << "\n";
                }
            }

            void processFunction ( Function * fn );
        };

        void InlinePatch::processFunction ( Function * fn ) {
            InlineCollect collect;
            fn->body->visit(collect);
            if ( collect.sites.empty() ) return;
            int inlineId = nextInlineId(fn);
            // a splice shifts the indices of later statements in the same block
            das_hash_map<ExprBlock *, int> indexShift;
            for ( auto & site : collect.sites ) {
                auto call = site.call;
                auto callee = call->func;
                if ( !site.stmt || !site.anchor.block ) {
                    error("can't inline " + callee->name + " here: the call is outside a function statement", call->at);
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
                bool siteLive = exprContains(site.stmt, call);
                if ( !siteLive && site.stmt->rtti_isWhile() ) {
                    siteLive = exprContains(static_cast<ExprWhile *>(site.stmt)->cond, call);
                }
                if ( !siteLive && site.stmt->rtti_isIfThenElse() ) {
                    auto lite = static_cast<ExprIfThenElse *>(site.stmt);
                    while ( lite->if_false && lite->if_false->rtti_isIfThenElse() ) {
                        auto inner = static_cast<ExprIfThenElse *>(lite->if_false);
                        if ( exprContains(inner->cond, call) ) { siteLive = true; break; }
                        lite = inner;
                    }
                }
                if ( !siteLive ) continue;
                if ( !calleeShapeOk(callee) ) continue;             // lint reports at the declaration
                if ( call->arguments.size() != callee->arguments.size() ) continue; // not fully inferred - defensive
                if ( callee->module != program->thisModule.get() ) {
                    auto & priv = privateUse(callee);
                    if ( !priv.empty() ) {
                        error("can't inline " + callee->name + " across modules: body uses private symbol '" + priv + "'", call->at);
                        continue;
                    }
                }
                // ----- classify arguments -----
                auto & stats = paramStats(callee);
                auto body = static_cast<ExprBlock *>(callee->body);
                bool isVoid = !callee->result || callee->result->isVoid();
                bool exprBody = body->list.size()==1 && body->list.back()->rtti_isReturn();
                das_hash_map<Variable *, ArgSub> paramSub;
                vector<ExpressionPtr> temps;
                for ( size_t ai=0, ais=call->arguments.size(); ai!=ais; ++ai ) {
                    auto & A = call->arguments[ai];
                    auto & P = callee->arguments[ai];
                    ArgSub sub;
                    bool byRefParam = P->type->ref || P->type->isRefType();
                    bool varParam = !P->type->constant;
                    Expression * leafA = A;
                    if ( leafA->rtti_isR2V() ) leafA = static_cast<ExprRef2Value *>(leafA)->subexpr;
                    bool leafConst = leafA->rtti_isConstant();
                    bool leafVar = leafA->rtti_isVar();
                    auto makeArgTemp = [&]( Expression * init, bool cnst, bool ref, bool viaMove ) {
                        string tname = "__inl" + to_string(inlineId) + "_arg_" + P->name;
                        temps.push_back(makeTemp(call->at, tname, init, cnst, ref, viaMove));
                        sub.tempName = tname;
                    };
                    if ( byRefParam ) {
                        if ( leafVar ) {
                            sub.substitute = leafA;             // same aliasing as the call itself
                        } else if ( A->type && A->type->ref ) {
                            // lvalue chain (field/index): bind a reference once, like the call did
                            auto init = A->clone();
                            init->alwaysSafe = true;            // generated binding to real storage
                            makeArgTemp(init, !varParam, true, false);
                        } else {
                            // rvalue into a const-ref param: materialize the value
                            bool nonCopyable = A->type && !A->type->canCopy();
                            makeArgTemp(A->clone(), true, false, nonCopyable);
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
                                auto & OP = callee->arguments[oi];
                                bool oRef = OP->type->ref || OP->type->isRefType();
                                if ( !oRef || OP->type->constant ) continue;
                                Expression * oleaf = call->arguments[oi];
                                if ( oleaf->rtti_isR2V() ) oleaf = static_cast<ExprRef2Value *>(oleaf)->subexpr;
                                if ( oleaf->rtti_isVar() && static_cast<ExprVar *>(oleaf)->variable==av->variable ) {
                                    hazard = true;
                                    break;
                                }
                            }
                            if ( !hazard && (av->isGlobalVariable() || av->variable->access_ref) ) {
                                // a global, or a local whose address escaped: the spliced
                                // body's writes could reach it, breaking snapshot semantics
                                hazard = !calleeWriteFree(callee);
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
                        bool orderSafe = calleeWriteFree(callee) || argReadsOnlyPrivateLocals(A, call, callee);
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
                    rewriter.tempAt = call->at;
                    auto ret = static_cast<ExprReturn *>(body->list.back());
                    ExpressionPtr callReplacement = nullptr;
                    if ( ret->subexpr ) {
                        callReplacement = ret->subexpr->clone()->visit(rewriter);
                    }
                    if ( site.stmt==call ) {
                        auto & list = site.anchor.block->list;
                        if ( callReplacement ) {
                            list[anchorIndex] = callReplacement;
                        } else {
                            list.erase(list.begin()+anchorIndex);
                            indexShift[site.anchor.block] -= 1;
                        }
                    } else {
                        ReplaceNode rn;
                        rn.what = call;
                        rn.with = callReplacement;
                        if ( !callReplacement ) {
                            error("can't inline void " + callee->name + " here: the call is not a statement", call->at);
                            continue;
                        }
                        auto & slot = site.anchor.block->list[anchorIndex];
                        slot = slot->visit(rn);
                        if ( !rn.done ) {
                            error("internal error: inlined call not found in its statement", call->at);
                            continue;
                        }
                    }
                    logSite(fn, call);
                    inlined ++;
                    inlineId ++;
                    changed = true;
                    continue;
                }
                // ----- statements needed: check the position, lower if necessary -----
                if ( site.stmt->rtti_isWhile() ) {
                    auto wh = static_cast<ExprWhile *>(site.stmt);
                    if ( exprContains(wh->cond, call) && wh->body->rtti_isBlock() ) {
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
                        if ( exprContains(inner->cond, call) || exprContains(ite->if_false, call) ) {
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
                auto pos = findPath(site.stmt, call, path);
                if ( pos==SitePosition::NotFound ) {
                    error("can't inline " + callee->name + " here: unsupported call position", call->at);
                    continue;
                }
                if ( pos==SitePosition::Unsupported ) {
                    error("can't inline " + callee->name + " inside ?? or a safe-navigation suffix - hoist the call into its own statement", call->at);
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
                        auto hoist = makeTemp(call->at, tname, lazy, true, false, false);
                        ReplaceNode rn;
                        rn.what = lazy;
                        rn.with = new ExprVar(call->at, tname);
                        list[anchorIndex] = list[anchorIndex]->visit(rn);
                        if ( !rn.done ) {
                            error("internal error: lazy operator not found in its statement", call->at);
                            continue;
                        }
                        list.insert(list.begin()+anchorIndex, hoist);
                        indexShift[site.anchor.block] += 1;
                        changed = true;
                        continue;
                    }
                    if ( !lazy->type ) {
                        error("can't inline " + callee->name + " here: missing type on the lazy operator", call->at);
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
                        error("can't inline " + callee->name + " here: unsupported lazy operator", call->at);
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
                collectImpurePrefix(site.stmt, call, prefix);
                vector<ExpressionPtr> splice;
                bool prefixFailed = false;
                int preIdx = 0;
                for ( auto pe : prefix ) {
                    if ( pe->type && pe->type->isVoid() ) {
                        // a void expression can only BE the statement, and then it has no prefix
                        error("can't inline " + callee->name + " here: void expression in the evaluation prefix", call->at);
                        prefixFailed = true;
                        break;
                    }
                    string tname = "__inl" + to_string(inlineId) + "_pre" + to_string(preIdx++);
                    splice.push_back(makeTemp(pe->at, tname, pe, true, false, false));
                    ReplaceNode rn;
                    rn.what = pe;
                    rn.with = new ExprVar(pe->at, tname);
                    auto & slot = site.anchor.block->list[anchorIndex];
                    slot = slot->visit(rn);
                    if ( !rn.done ) {
                        error("internal error: prefix expression not found in its statement", call->at);
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
                names.prefix = "__inl" + to_string(inlineId) + "_";
                callee->body->visit(names);
                InlineBodyRewriter rewriter;
                rewriter.paramSub = &paramSub;
                rewriter.rename = &rename;
                rewriter.tempAt = call->at;
                ExpressionPtr callReplacement = nullptr;
                if ( exprBody ) {
                    auto ret = static_cast<ExprReturn *>(body->list.back());
                    if ( ret->subexpr ) {
                        callReplacement = ret->subexpr->clone()->visit(rewriter);
                    }
                } else {
                    auto bodyClone = static_cast<ExprBlock *>(callee->body->clone());
                    ExpressionPtr trailing = nullptr;
                    if ( !bodyClone->list.empty() && bodyClone->list.back()->rtti_isReturn() ) {
                        trailing = bodyClone->list.back();
                        bodyClone->list.pop_back();
                    }
                    if ( !isVoid ) {
                        string resName = "__inl" + to_string(inlineId) + "_res";
                        splice.push_back(makeUninitDecl(call->at, resName, callee->result));
                        auto ret = static_cast<ExprReturn *>(trailing);
                        bodyClone->list.push_back(new ExprCopy(ret->at,
                            new ExprVar(ret->at, resName), ret->subexpr));
                        callReplacement = new ExprVar(call->at, resName);
                    }
                    splice.push_back(bodyClone->visit(rewriter));
                }
                auto & list = site.anchor.block->list;
                list.insert(list.begin()+anchorIndex, splice.begin(), splice.end());
                indexShift[site.anchor.block] += int(splice.size());
                int stmtIndex = anchorIndex + int(splice.size());
                if ( list[stmtIndex]==call ) {
                    // the call IS the statement
                    if ( callReplacement ) {
                        list[stmtIndex] = callReplacement;
                    } else {
                        list.erase(list.begin()+stmtIndex);
                        indexShift[site.anchor.block] -= 1;
                    }
                } else {
                    ReplaceNode rn;
                    rn.what = call;
                    rn.with = callReplacement;
                    list[stmtIndex] = list[stmtIndex]->visit(rn);
                    if ( !rn.done ) {
                        error("internal error: inlined call not found in its statement", call->at);
                        continue;
                    }
                }
                logSite(fn, call);
                inlined ++;
                inlineId ++;
                changed = true;
            }
        }

        // DFS postorder over the inline graph inside this module, [inline] functions
        // first: a chain f -> g -> h splices already-inlined bodies in a single round
        void orderInlineFunctions ( Module * thisMod, Function * fn,
                vector<Function *> & order, das_hash_set<Function *> & seen ) {
            if ( !fn->body || fn->isTemplate || fn->stub ) return;
            if ( fn->module != thisMod ) return;
            if ( !seen.insert(fn).second ) return;
            lookupExpressions(fn->body, [&](Expression * expr) {
                if ( expr->rtti_isCall() ) {
                    auto call = static_cast<ExprCall *>(expr);
                    if ( call->func && call->func->mustInline ) {
                        orderInlineFunctions(thisMod, call->func, order, seen);
                    }
                }
            });
            order.push_back(fn);
        }

    } // anonymous namespace

    bool Program::patchInline() {
        if ( options.getBoolOption("disable_inline", policies.disable_inline) ) return false;
        // cheap gate: any [inline] function visible at all?
        bool anyInline = false;
        library.foreach([&](Module * mod) -> bool {
            if ( !anyInline ) {
                mod->functions.find_first([&](auto fn) {
                    if ( fn->mustInline ) { anyInline = true; return true; }
                    return false;
                });
            }
            return true;
        }, "*");
        if ( !anyInline ) return false;
        InlinePatch patch;
        patch.program = this;
        patch.logs = daScriptEnvironment::getBound()->g_compilerLog;
        patch.logOpt = options.getBoolOption("log_optimization", false);
        vector<Function *> order;
        das_hash_set<Function *> seen;
        thisModule->functions.foreach([&](auto fn) {
            if ( fn->mustInline ) orderInlineFunctions(thisModule.get(), fn, order, seen);
        });
        thisModule->functions.foreach([&](auto fn) {
            orderInlineFunctions(thisModule.get(), fn, order, seen);
        });
        for ( auto fn : order ) {
            patch.processFunction(fn);
            if ( failed() ) break;
        }
        if ( patch.logOpt && patch.logs && patch.inlined ) {
            *patch.logs << "INLINE: " << patch.inlined << " call site(s) in module " << thisModule->name << "\n";
        }
        return patch.changed;
    }

}
