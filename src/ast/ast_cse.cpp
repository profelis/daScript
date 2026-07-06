#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_visitor.h"
#include "daScript/ast/ast_expressions.h"
#include "daScript/ast/ast_cfg.h"
#include "daScript/misc/anyhash.h"

namespace das {

    // ===== Common-subexpression elimination (value reuse) =====
    // Replaces a pure expression E with a read of a local t when a statement-level
    // `let t = E` / `t = E` is available on every path to the occurrence (forward
    // availability over the statement-level CFG, ast_cfg.h) and t's declaration is
    // lexically visible there. No temps are created and no statements are inserted -
    // v1 only reuses values the program already named, so every rewrite strictly
    // removes work. Reuse is bit-exact (the reused value came from the same pure
    // computation over unchanged inputs), so there is no fast_math gate.
    //
    // Soundness model (deliberately narrow):
    //  * leaves are ExprLet locals and function arguments of by-value types (non-ref,
    //    non-refType) where every occurrence is a value read (r2v) or the left side
    //    of a statement-level ExprCopy - anything else (addr(), by-ref pass,
    //    field/index/swizzle access, op-assign, ref binding, clone/move target)
    //    disqualifies the variable, which rules out invisible writes;
    //  * candidate expressions are side-effect-free trees of Op1/Op2/Op3/Call/Cast/
    //    Swizzle over leaves and constants - no memory reads (field/at/deref), so a
    //    candidate's value can only change through a visible store to a leaf;
    //  * pointer/handle-returning calls are excluded even when flagged pure: a
    //    factory like clone_type returns a fresh, uniquely-owned node per
    //    evaluation - value-equal is not identity-equal (found live in
    //    daslib/linq_fold_common, where merging two clone_type calls aliased one
    //    TypeDecl into two owners);
    //  * pairs (E -> t) come from `let t = E` and statement-level `t = E` where t is
    //    itself a clean local; a store to any leaf mentioned by E (or to t) kills the
    //    pair; make-block interiors neither generate pairs nor get rewritten;
    //  * a rewrite additionally requires t's declaration to be lexically visible at
    //    the occurrence - dataflow availability alone is not enough: a pair born in a
    //    closed `{ }` scope may still be "available" after it, while t's stack slot
    //    is already reused by a sibling scope;
    //  * functions carrying control flow the CFG does not model are skipped whole:
    //    goto/label (also covers lowered generators), try/recover, and non-empty
    //    finally - same rule as DSE (ast_dse.cpp).

    namespace {

        struct CseAnchor {
            ExprBlock * block = nullptr;
            int         index = -1;     // statement index within the block
        };

        // one walk: (a) bail on constructs the CFG does not model, (b) collect
        // candidate leaves and their declaration anchors, (c) disqualify any variable
        // with a use that is not a plain value read and not the lvalue of a
        // statement-level assignment, (d) record the lexical anchor of every
        // expression the CFG carries as a statement (block statements, if/while
        // conditions, for sources, with subjects) for the scope-visibility check
        class CsePrescan : public Visitor {
        public:
            bool eligible = true;
            vector<Variable *> locals;                      // ExprLet locals of by-value type, in order
            das_hash_set<Variable *> disq;                  // variables with an aliasing-capable use
            das_hash_set<Expression *> storeLefts;          // lvalue ExprVar nodes of statement-level copies
            das_hash_set<Expression *> swizzleReads;        // ExprVar nodes under a value-read swizzle
            das_hash_map<Variable *, CseAnchor> declAt;     // where each local's ExprLet sits
            das_hash_map<Expression *, CseAnchor> anchorOf; // lexical anchor of potential CFG statements
            das_hash_map<ExprBlock *, CseAnchor> blockParent;
        protected:
            vector<CseAnchor> blockStack;
            Expression * curStmt = nullptr;
            CseAnchor curAnchor () const {
                return blockStack.empty() ? CseAnchor() : blockStack.back();
            }
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprBlock * blk ) override {
                Visitor::preVisit(blk);
                if ( !blk->finalList.empty() ) eligible = false;
                blockParent[blk] = curAnchor();
                blockStack.push_back(CseAnchor{blk, -1});
            }
            virtual ExpressionPtr visit ( ExprBlock * blk ) override {
                blockStack.pop_back();
                return Visitor::visit(blk);
            }
            virtual void preVisitBlockExpression ( ExprBlock * block, Expression * expr ) override {
                Visitor::preVisitBlockExpression(block, expr);
                if ( !blockStack.empty() && blockStack.back().block==block ) blockStack.back().index++;
                anchorOf[expr] = curAnchor();
                curStmt = expr;
            }
            virtual void preVisit ( ExprTryCatch * expr ) override {
                Visitor::preVisit(expr);
                eligible = false;
            }
            virtual void preVisit ( ExprGoto * expr ) override {
                Visitor::preVisit(expr);
                eligible = false;
            }
            virtual void preVisit ( ExprLabel * expr ) override {
                Visitor::preVisit(expr);
                eligible = false;
            }
            virtual void preVisit ( ExprYield * expr ) override {
                Visitor::preVisit(expr);
                eligible = false;
            }
            virtual void preVisit ( ExprCopy * expr ) override {
                Visitor::preVisit(expr);
                if ( expr==curStmt && expr->left->rtti_isVar() ) {
                    storeLefts.insert(expr->left);
                }
            }
            virtual void preVisitLet ( ExprLet * let, const VariablePtr & var, bool last ) override {
                Visitor::preVisitLet(let, var, last);
                if ( var->type && !var->type->ref && !var->type->isRefType() ) {
                    locals.push_back(var);
                    declAt[var] = curAnchor();
                }
            }
            virtual void preVisit ( ExprSwizzle * expr ) override {
                Visitor::preVisit(expr);
                // a value-read swizzle over a by-value local (v.x with r2v) cannot
                // write or alias the variable - keep it a clean use
                if ( expr->r2v && !expr->write && expr->value->rtti_isVar() ) {
                    swizzleReads.insert(expr->value);
                }
            }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( !expr->r2v && storeLefts.find(expr)==storeLefts.end()
                    && swizzleReads.find(expr)==swizzleReads.end() ) {
                    disq.insert(expr->variable);
                }
            }
            virtual void preVisit ( ExprIfThenElse * expr ) override {
                Visitor::preVisit(expr);
                anchorOf[expr->cond] = curAnchor();
            }
            virtual void preVisit ( ExprWhile * expr ) override {
                Visitor::preVisit(expr);
                anchorOf[expr->cond] = curAnchor();
            }
            virtual void preVisit ( ExprFor * expr ) override {
                Visitor::preVisit(expr);
                for ( auto & src : expr->sources ) anchorOf[src] = curAnchor();
            }
            virtual void preVisit ( ExprWith * expr ) override {
                Visitor::preVisit(expr);
                anchorOf[expr->with] = curAnchor();
            }
        };

        // a side-effect-free call returning a pointer/handle may still be a FACTORY
        // (clone_type & co return a fresh node each evaluation): results are
        // value-equal but not identity-equal, and reuse would alias something the
        // caller treats as uniquely owned. Builtin pointer operators (p + i) are
        // arithmetic, not allocation, and stay eligible.
        bool cseIdentityProducing ( Expression * e, Function * func ) {
            if ( !e->type ) return true;
            if ( !e->type->isPointer() && e->type->baseType!=Type::tHandle ) return false;
            if ( e->rtti_isCall() ) return true;
            return func && !func->builtIn;
        }

        // whitelisted pure value tree over clean leaves and constants (no memory
        // reads); collects the leaf variables the tree mentions
        bool cseAllowedTree ( Expression * e, const das_hash_set<Variable *> & leaves, vector<Variable *> & mentions ) {
            if ( !e ) return false;
            if ( e->rtti_isConstant() ) return true;
            if ( e->rtti_isVar() ) {
                auto v = static_cast<ExprVar *>(e);
                if ( v->write || !v->variable ) return false;
                if ( leaves.find(v->variable)==leaves.end() ) return false;
                mentions.push_back(v->variable);
                return true;
            }
            if ( e->rtti_isR2V() ) {
                return cseAllowedTree(static_cast<ExprRef2Value *>(e)->subexpr, leaves, mentions);
            }
            if ( e->rtti_isCopy() || e->rtti_isClone() || e->rtti_isSequence() ) return false;
            if ( e->rtti_isOp3() ) {
                auto op = static_cast<ExprOp3 *>(e);
                if ( cseIdentityProducing(e, op->func) ) return false;
                return cseAllowedTree(op->subexpr, leaves, mentions)
                    && cseAllowedTree(op->left, leaves, mentions)
                    && cseAllowedTree(op->right, leaves, mentions);
            }
            if ( e->rtti_isOp2() ) {    // ExprMove's write-flagged left is caught by the ExprVar rule
                auto op = static_cast<ExprOp2 *>(e);
                if ( cseIdentityProducing(e, op->func) ) return false;
                return cseAllowedTree(op->left, leaves, mentions)
                    && cseAllowedTree(op->right, leaves, mentions);
            }
            if ( e->rtti_isOp1() ) {
                auto op = static_cast<ExprOp1 *>(e);
                if ( cseIdentityProducing(e, op->func) ) return false;
                return cseAllowedTree(op->subexpr, leaves, mentions);
            }
            if ( e->rtti_isCall() ) {
                auto c = static_cast<ExprCall *>(e);
                if ( !c->func ) return false;
                if ( cseIdentityProducing(e, c->func) ) return false;
                for ( auto & arg : c->arguments ) {
                    if ( !cseAllowedTree(arg, leaves, mentions) ) return false;
                }
                return true;
            }
            if ( e->rtti_isCast() ) {
                return cseAllowedTree(static_cast<ExprCast *>(e)->subexpr, leaves, mentions);
            }
            if ( e->rtti_isSwizzle() ) {
                auto s = static_cast<ExprSwizzle *>(e);
                return !s->write && cseAllowedTree(s->value, leaves, mentions);
            }
            return false;   // unrecognized class - conservatively out
        }

        // candidate root: a real operation yielding a by-value result, side-effect free
        bool cseCandidateRoot ( Expression * e ) {
            if ( !e || !e->type ) return false;
            if ( !e->noSideEffects ) return false;
            if ( !(e->rtti_isOp1() || e->rtti_isOp2() || e->rtti_isOp3()
                || e->rtti_isCall() || e->rtti_isCast() || e->rtti_isSwizzle()) ) return false;
            if ( e->rtti_isCopy() || e->rtti_isClone() || e->rtti_isSequence() ) return false;
            if ( e->type->ref || e->type->isRefType() ) return false;
            if ( e->type->baseType==Type::tVoid ) return false;
            return true;
        }

        // bucketing companion to Expression::sameAs - collisions are fine (verified
        // by sameAs), a hash mismatch for sameAs-equal trees is not
        uint64_t cseHash ( Expression * e ) {
            if ( !e ) return 0;
            uint64_t h = hash_blockz64((const uint8_t *) e->__rtti);
            auto mix = [&]( uint64_t v ) { h = (h ^ v) * 1099511628211ul; };
            if ( e->rtti_isConstant() ) {
                auto c = static_cast<ExprConst *>(e);
                mix(uint64_t(c->baseType));
                if ( e->rtti_isStringConstant() ) {
                    mix(hash_blockz64((const uint8_t *) static_cast<ExprConstString *>(e)->text.c_str()));
                } else {
                    mix(hash_block64((const uint8_t *) &c->value, sizeof(vec4f)));
                }
            } else if ( e->rtti_isVar() ) {
                mix(uint64_t(uintptr_t(static_cast<ExprVar *>(e)->variable)));
            } else if ( e->rtti_isR2V() ) {
                mix(cseHash(static_cast<ExprRef2Value *>(e)->subexpr));
            } else if ( e->rtti_isOp3() ) {
                auto op = static_cast<ExprOp3 *>(e);
                mix(hash_blockz64((const uint8_t *) op->op.c_str()));
                mix(uint64_t(uintptr_t(op->func)));
                mix(cseHash(op->subexpr));
                mix(cseHash(op->left));
                mix(cseHash(op->right));
            } else if ( e->rtti_isOp2() ) {
                auto op = static_cast<ExprOp2 *>(e);
                mix(hash_blockz64((const uint8_t *) op->op.c_str()));
                mix(uint64_t(uintptr_t(op->func)));
                mix(cseHash(op->left));
                mix(cseHash(op->right));
            } else if ( e->rtti_isOp1() ) {
                auto op = static_cast<ExprOp1 *>(e);
                mix(hash_blockz64((const uint8_t *) op->op.c_str()));
                mix(uint64_t(uintptr_t(op->func)));
                mix(cseHash(op->subexpr));
            } else if ( e->rtti_isCall() ) {
                auto c = static_cast<ExprCall *>(e);
                mix(uint64_t(uintptr_t(c->func)));
                for ( auto & arg : c->arguments ) mix(cseHash(arg));
            } else if ( e->rtti_isCast() ) {
                auto c = static_cast<ExprCast *>(e);
                if ( c->castType ) mix(uint64_t(c->castType->baseType));
                mix(cseHash(c->subexpr));
            } else if ( e->rtti_isSwizzle() ) {
                auto s = static_cast<ExprSwizzle *>(e);
                if ( !s->fields.empty() ) mix(hash_block64((const uint8_t *) s->fields.data(), s->fields.size()));
                mix(cseHash(s->value));
            }
            return h;
        }

        struct CsePair {
            Expression *        expr = nullptr;    // canonical E
            Variable *          var = nullptr;     // clean local holding E's value
            uint64_t            hash = 0;
            vector<Variable *>  mentions;           // leaf variables E reads
        };

        struct CseStmtInfo {
            vector<int>         gen;                // pairs this statement (re)establishes
            vector<Variable *>  declVars;           // let-declared here (kill, before gen)
            vector<Variable *>  storeVars;          // stored-to leaves in subtree (kill, before gen)
        };

        // stores to candidate leaves anywhere in a statement's subtree, including
        // make-block interiors (a block argument body runs during the statement)
        class CseWrites : public Visitor {
        public:
            CseWrites ( const das_hash_set<Expression *> & sl ) : storeLefts(sl) {}
            vector<Variable *> writes;
        protected:
            const das_hash_set<Expression *> & storeLefts;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( storeLefts.find(expr)!=storeLefts.end() ) writes.push_back(expr->variable);
            }
        };

        // per-statement occurrence matcher: top-down, skips make-block interiors
        // (their execution count is unknown) and the inside of matched subtrees
        class CseMatch : public Visitor {
        public:
            CseMatch ( const vector<CsePair> & ps, const das_hash_map<uint64_t, vector<int>> & bh,
                       const CsePrescan & sc, das_hash_map<Expression *, Variable *> & pl )
                : pairs(ps), byHash(bh), scan(sc), plan(pl) {}
            void setStatement ( const vector<uint64_t> & av, const CseStmtInfo * si, const CseAnchor & anch ) {
                avail = &av;
                anchored = anch.block!=nullptr;
                anchor = anch;
                touched.clear();
                if ( si ) {
                    for ( auto v : si->declVars ) touched.insert(v);
                    for ( auto v : si->storeVars ) touched.insert(v);
                }
                suppress = 0;
            }
        protected:
            const vector<CsePair> & pairs;
            const das_hash_map<uint64_t, vector<int>> & byHash;
            const CsePrescan & scan;
            das_hash_map<Expression *, Variable *> & plan;
            const vector<uint64_t> * avail = nullptr;
            das_hash_set<Variable *> touched;   // vars this statement declares or stores to
            CseAnchor anchor;
            bool anchored = false;
            int suppress = 0;
            bool scopeValid ( Variable * v ) const {
                auto dit = scan.declAt.find(v);
                if ( dit==scan.declAt.end() ) return false;
                CseAnchor a = anchor;
                while ( a.block ) {
                    if ( a.block==dit->second.block ) return a.index > dit->second.index;
                    auto pit = scan.blockParent.find(a.block);
                    if ( pit==scan.blockParent.end() ) return false;
                    a = pit->second;
                }
                return false;
            }
            bool match ( Expression * expr, Variable *& out ) const {
                if ( !anchored || !avail ) return false;
                if ( !cseCandidateRoot(expr) ) return false;
                auto bit = byHash.find(cseHash(expr));
                if ( bit==byHash.end() ) return false;
                for ( int pi : bit->second ) {
                    if ( !(((*avail)[pi>>6] >> (pi&63)) & 1) ) continue;
                    auto & P = pairs[pi];
                    // no reuse across a statement that writes P's inputs or holder -
                    // intra-statement evaluation order is not modeled
                    if ( touched.find(P.var)!=touched.end() ) continue;
                    bool touchedMention = false;
                    for ( auto m : P.mentions ) {
                        if ( touched.find(m)!=touched.end() ) { touchedMention = true; break; }
                    }
                    if ( touchedMention ) continue;
                    if ( !scopeValid(P.var) ) continue;
                    if ( !P.expr->sameAs(expr) ) continue;
                    out = P.var;
                    return true;
                }
                return false;
            }
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual bool canVisitMakeBlockBody ( ExprMakeBlock * ) override { return false; }
            virtual void preVisitExpression ( Expression * expr ) override {
                Visitor::preVisitExpression(expr);
                if ( suppress ) { suppress++; return; }
                Variable * v = nullptr;
                if ( match(expr, v) ) {
                    plan[expr] = v;
                    suppress = 1;
                }
            }
            virtual ExpressionPtr visitExpression ( Expression * expr ) override {
                if ( suppress ) suppress--;
                return Visitor::visitExpression(expr);
            }
        };

        void analyzeCse ( Function * fn, das_hash_map<Expression *, Variable *> & plan ) {
            CsePrescan scan;
            fn->body->visit(scan);
            if ( !scan.eligible ) return;
            // leaf universe: clean by-value locals and arguments
            das_hash_set<Variable *> leaves;
            for ( auto v : scan.locals ) {
                if ( scan.disq.find(v)==scan.disq.end() ) leaves.insert(v);
            }
            for ( auto & arg : fn->arguments ) {
                if ( arg->type && !arg->type->ref && !arg->type->isRefType()
                    && scan.disq.find(arg)==scan.disq.end() ) leaves.insert(arg);
            }
            if ( leaves.empty() ) return;
            Cfg cfg = buildCfg(fn);
            // pair and per-statement gen/kill collection
            vector<CsePair> pairs;
            das_hash_map<uint64_t, vector<int>> byHash;
            das_hash_map<Expression *, CseStmtInfo> stmtInfo;
            auto addPair = [&]( Expression * stmt, Expression * E, Variable * v ) {
                if ( !E || !cseCandidateRoot(E) ) return;
                vector<Variable *> mentions;
                if ( !cseAllowedTree(E, leaves, mentions) ) return;
                for ( auto m : mentions ) {
                    if ( m==v ) return;     // t = f(t): stale the moment the store lands
                }
                uint64_t h = cseHash(E);
                auto & bucket = byHash[h];
                for ( int pi : bucket ) {
                    if ( pairs[pi].var==v && pairs[pi].expr->sameAs(E) ) {
                        stmtInfo[stmt].gen.push_back(pi);
                        return;
                    }
                }
                int idx = int(pairs.size());
                pairs.push_back(CsePair{E, v, h, mentions});
                bucket.push_back(idx);
                stmtInfo[stmt].gen.push_back(idx);
            };
            for ( auto b : cfg.blocks ) {
                for ( auto stmt : b->stmts ) {
                    auto & SI = stmtInfo[stmt];
                    CseWrites w(scan.storeLefts);
                    stmt->visit(w);
                    SI.storeVars = w.writes;
                    if ( stmt->rtti_isLet() ) {
                        auto let = static_cast<ExprLet *>(stmt);
                        for ( auto & pv : let->variables ) {
                            SI.declVars.push_back(pv);
                            if ( leaves.find(pv)==leaves.end() ) continue;
                            if ( pv->init_via_move || pv->init_via_clone ) continue;
                            addPair(stmt, pv->init, pv);
                        }
                    } else if ( stmt->rtti_isCopy() ) {
                        auto cp = static_cast<ExprCopy *>(stmt);
                        if ( cp->left->rtti_isVar() ) {
                            auto v = static_cast<ExprVar *>(cp->left)->variable;
                            if ( leaves.find(v)!=leaves.end()
                                && scan.declAt.find(v)!=scan.declAt.end() ) {
                                addPair(stmt, cp->right, v);
                            }
                        }
                    }
                }
            }
            if ( pairs.empty() ) return;
            das_hash_map<Variable *, vector<int>> pairsTouchingVar;
            for ( int i=0, is=int(pairs.size()); i!=is; ++i ) {
                pairsTouchingVar[pairs[i].var].push_back(i);
                for ( auto m : pairs[i].mentions ) pairsTouchingVar[m].push_back(i);
            }
            size_t np = pairs.size();
            size_t nw = (np + 63) / 64;
            size_t nb = cfg.blocks.size();
            auto killVar = [&]( Variable * v, vector<uint64_t> & avail ) {
                auto it = pairsTouchingVar.find(v);
                if ( it==pairsTouchingVar.end() ) return;
                for ( int pi : it->second ) avail[pi>>6] &= ~(1ull<<(pi&63));
            };
            // kills first, then gen: a store's rhs was computed before the store
            // landed, and self-referencing pairs were rejected at creation
            auto applyStmt = [&]( Expression * stmt, vector<uint64_t> & avail ) {
                auto it = stmtInfo.find(stmt);
                if ( it==stmtInfo.end() ) return;
                auto & SI = it->second;
                for ( auto v : SI.declVars ) killVar(v, avail);
                for ( auto v : SI.storeVars ) killVar(v, avail);
                for ( int g : SI.gen ) avail[g>>6] |= 1ull<<(g&63);
            };
            // forward availability to fixpoint: IN = intersection over predecessors,
            // non-entry blocks start at the universe set
            vector<vector<uint64_t>> IN(nb), OUT(nb);
            for ( size_t i=0; i!=nb; ++i ) {
                IN[i].assign(nw, ~0ull);
                OUT[i].assign(nw, ~0ull);
            }
            IN[cfg.entry->id].assign(nw, 0);
            vector<uint64_t> cur(nw);
            bool changed = true;
            while ( changed ) {
                changed = false;
                for ( auto b : cfg.blocks ) {
                    if ( b!=cfg.entry && !b->pred.empty() ) {
                        for ( size_t w=0; w!=nw; ++w ) cur[w] = ~0ull;
                        for ( auto p : b->pred ) {
                            auto & pout = OUT[p->id];
                            for ( size_t w=0; w!=nw; ++w ) cur[w] &= pout[w];
                        }
                        if ( cur!=IN[b->id] ) { IN[b->id] = cur; changed = true; }
                    }
                    cur = IN[b->id];
                    for ( auto stmt : b->stmts ) applyStmt(stmt, cur);
                    if ( cur!=OUT[b->id] ) { OUT[b->id] = cur; changed = true; }
                }
            }
            // final scan: mark rewritable occurrences
            CseMatch matcher(pairs, byHash, scan, plan);
            for ( auto b : cfg.blocks ) {
                cur = IN[b->id];
                for ( auto stmt : b->stmts ) {
                    auto sit = stmtInfo.find(stmt);
                    auto ait = scan.anchorOf.find(stmt);
                    matcher.setStatement(cur, sit!=stmtInfo.end() ? &sit->second : nullptr,
                        ait!=scan.anchorOf.end() ? ait->second : CseAnchor());
                    stmt->visit(matcher);
                    applyStmt(stmt, cur);
                }
            }
        }

        class EliminateCse : public PassVisitor {
        public:
            using PassVisitor::PassVisitor;
            using PassVisitor::visit;
        protected:
            das_hash_map<Expression *, Variable *> plan;
            virtual bool canVisitFunction ( Function * fun ) override {
                if ( fun->stub || fun->isTemplate || !funcIsDirty(fun) ) return false;
                if ( !fun->body || !fun->body->rtti_isBlock() ) return false;
                plan.clear();
                analyzeCse(fun, plan);
                return !plan.empty();
            }
            virtual bool canVisitStructure ( Structure * ) override { return false; }
            virtual bool canVisitStructureFieldInit ( Structure * ) override { return false; }
            virtual bool canVisitArgumentInit ( Function *, const VariablePtr &, Expression * ) override { return false; }
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual bool canVisitGlobalVariable ( Variable * ) override { return false; }
            virtual bool canVisitEnumeration ( Enumeration * ) override { return false; }
            virtual ExpressionPtr visitExpression ( Expression * expr ) override {
                auto it = plan.find(expr);
                if ( it==plan.end() ) return Visitor::visitExpression(expr);
                auto var = it->second;
                auto evar = new ExprVar(expr->at, var->name);
                evar->variable = var;
                evar->local = true;
                evar->r2v = true;
                evar->type = new TypeDecl(*var->type);
                evar->type->ref = false;
                reportFolding();
                return evar;
            }
        };
    }

    // program

    bool Program::optimizationCSE(int32_t round) {
        if ( options.getBoolOption("disable_cse", false) ) return false;
        checkSideEffects();
        EliminateCse pass(round);
        visit(pass);
        return pass.didAnything();
    }
}
