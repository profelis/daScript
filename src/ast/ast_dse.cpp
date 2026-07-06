#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_visitor.h"
#include "daScript/ast/ast_expressions.h"
#include "daScript/ast/ast_cfg.h"

namespace das {

    // ===== Dead-store elimination =====
    // Removes a statement-level `x = <rhs>` when x is a plain by-value local with no
    // aliasing uses, the rhs is pure, and no path from the store reaches a read of x
    // before the next full overwrite. Liveness runs backward over the statement-level
    // CFG (ast_cfg.h).
    //
    // Soundness model (deliberately narrow):
    //  * candidates are ExprLet locals of non-ref, non-refType types (the pass-by-value
    //    world: workhorse scalars, pointers, enums, bitfields, ranges, vectors, string) -
    //    ExprCopy on them is a plain value write with no copy hooks;
    //  * every occurrence of a candidate must be a value read (r2v) or the left side of a
    //    statement-level ExprCopy. Anything else (addr(), by-ref pass, field/index/swizzle
    //    access, op-assign, ref binding, clone/move target) disqualifies the variable -
    //    this is what rules out invisible aliases;
    //  * a store inside an opaque statement (make-block body, unsafe block) is never a
    //    removal candidate or a kill - any candidate mention inside an opaque statement
    //    makes the variable live there (over-approximation, sound);
    //  * functions carrying control flow the CFG does not model are skipped whole:
    //    goto/label (also covers lowered generators), try/recover, and non-empty finally
    //    (it also runs on an early return the CFG routes straight to exit).
    // Local stores are unobservable after a panic (locals die with the frame; finally is
    // skipped on panic by design), so removal needs no panic-path modeling.

    namespace {

        // one walk: (a) bail on constructs the CFG does not model, (b) collect candidate
        // locals, (c) disqualify any variable with a use that is not a plain value read
        // and not the lvalue of a statement-level assignment
        class DsePrescan : public Visitor {
        public:
            bool eligible = true;
            vector<Variable *> locals;                  // ExprLet locals of by-value type, in order
            das_hash_set<Variable *> disq;              // variables with an aliasing-capable use
            das_hash_set<Variable *> storedVars;        // variables with at least one statement-level store
        protected:
            das_hash_set<Expression *> storeLefts;      // lvalue ExprVar nodes of statement-level copies
            Expression * curStmt = nullptr;
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprBlock * blk ) override {
                Visitor::preVisit(blk);
                if ( !blk->finalList.empty() ) eligible = false;
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
            virtual void preVisitBlockExpression ( ExprBlock * block, Expression * expr ) override {
                Visitor::preVisitBlockExpression(block, expr);
                curStmt = expr;
            }
            virtual void preVisit ( ExprCopy * expr ) override {
                Visitor::preVisit(expr);
                if ( expr==curStmt && expr->left->rtti_isVar() ) {
                    storeLefts.insert(expr->left);
                    storedVars.insert(((ExprVar *)expr->left)->variable);
                }
            }
            virtual void preVisitLet ( ExprLet * let, const VariablePtr & var, bool last ) override {
                Visitor::preVisitLet(let, var, last);
                if ( var->type && !var->type->ref && !var->type->isRefType() ) {
                    locals.push_back(var);
                }
            }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                if ( !expr->r2v && storeLefts.find(expr)==storeLefts.end() ) {
                    disq.insert(expr->variable);
                }
            }
        };

        // collect candidate-variable mentions (any occurrence) in a subtree
        class DseMentions : public Visitor {
        public:
            DseMentions ( const das_hash_map<Variable *,int> & idx, vector<int> & out )
                : index(idx), uses(out) {}
        protected:
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual void preVisit ( ExprVar * expr ) override {
                Visitor::preVisit(expr);
                auto it = index.find(expr->variable);
                if ( it!=index.end() ) uses.push_back(it->second);
            }
        protected:
            const das_hash_map<Variable *,int> & index;
            vector<int> & uses;
        };

        struct DseStmt {
            int killVar = -1;       // candidate index fully overwritten by this statement
            bool rhsPure = false;   // store rhs carries no side effects (safe to not evaluate)
            vector<int> uses;       // candidate mentions (store: rhs only; otherwise whole subtree)
        };

        void analyzeDeadStores ( Function * fn, das_hash_set<Expression *> & dead ) {
            DsePrescan scan;
            fn->body->visit(scan);
            if ( !scan.eligible ) return;
            das_hash_map<Variable *,int> index;
            for ( auto v : scan.locals ) {
                if ( scan.disq.find(v)!=scan.disq.end() ) continue;
                if ( scan.storedVars.find(v)==scan.storedVars.end() ) continue;  // nothing to remove
                int idx = int(index.size());
                index[v] = idx;
            }
            if ( index.empty() ) return;
            Cfg cfg = buildCfg(fn);
            size_t nw = (index.size() + 63) / 64;
            struct BlockInfo {
                vector<DseStmt>  stmts;
                vector<uint64_t> liveIn, liveOut;
            };
            vector<BlockInfo> binfo(cfg.blocks.size());
            for ( size_t bi=0, bis=cfg.blocks.size(); bi!=bis; ++bi ) {
                auto b = cfg.blocks[bi];
                auto & BI = binfo[bi];
                BI.liveIn.resize(nw, 0);
                BI.liveOut.resize(nw, 0);
                BI.stmts.resize(b->stmts.size());
                for ( size_t si=0, sis=b->stmts.size(); si!=sis; ++si ) {
                    auto stmt = b->stmts[si];
                    auto & SI = BI.stmts[si];
                    if ( stmt->rtti_isCopy() ) {
                        auto cp = (ExprCopy *) stmt;
                        if ( cp->left->rtti_isVar() ) {
                            auto it = index.find(((ExprVar *)cp->left)->variable);
                            if ( it!=index.end() ) {
                                SI.killVar = it->second;
                                SI.rhsPure = cp->right->noSideEffects;
                                DseMentions m(index, SI.uses);
                                cp->right->visit(m);
                                continue;
                            }
                        }
                    }
                    DseMentions m(index, SI.uses);
                    stmt->visit(m);
                }
            }
            // backward liveness to fixpoint. blocks are numbered in creation order, so
            // reverse order approximates reverse topological order and converges fast
            vector<uint64_t> live(nw);
            bool changed = true;
            while ( changed ) {
                changed = false;
                for ( size_t bi=cfg.blocks.size(); bi-->0; ) {
                    auto b = cfg.blocks[bi];
                    auto & BI = binfo[bi];
                    for ( auto & w : BI.liveOut ) w = 0;
                    for ( auto s : b->succ ) {
                        auto & sin = binfo[s->id].liveIn;
                        for ( size_t w=0; w!=nw; ++w ) BI.liveOut[w] |= sin[w];
                    }
                    live = BI.liveOut;
                    for ( size_t si=BI.stmts.size(); si-->0; ) {
                        auto & SI = BI.stmts[si];
                        if ( SI.killVar>=0 ) live[SI.killVar>>6] &= ~(1ull<<(SI.killVar&63));
                        for ( int u : SI.uses ) live[u>>6] |= 1ull<<(u&63);
                    }
                    if ( live != BI.liveIn ) { BI.liveIn = live; changed = true; }
                }
            }
            // final scan: a store whose target is dead after it and whose rhs is pure is
            // removed - it neither kills (target already dead) nor gens (rhs not evaluated),
            // which lets a chain of dead stores fall in a single pass
            for ( size_t bi=0, bis=cfg.blocks.size(); bi!=bis; ++bi ) {
                auto b = cfg.blocks[bi];
                auto & BI = binfo[bi];
                live = BI.liveOut;
                for ( size_t si=BI.stmts.size(); si-->0; ) {
                    auto & SI = BI.stmts[si];
                    if ( SI.killVar>=0 ) {
                        bool isLive = ((live[SI.killVar>>6] >> (SI.killVar&63)) & 1) != 0;
                        if ( !isLive && SI.rhsPure ) {
                            dead.insert(b->stmts[si]);
                            continue;
                        }
                        live[SI.killVar>>6] &= ~(1ull<<(SI.killVar&63));
                    }
                    for ( int u : SI.uses ) live[u>>6] |= 1ull<<(u&63);
                }
            }
        }

        class EliminateDeadStores : public PassVisitor {
        public:
            using PassVisitor::PassVisitor;
            using PassVisitor::visit;
        protected:
            das_hash_set<Expression *> dead;
            virtual bool canVisitFunction ( Function * fun ) override {
                if ( fun->stub || fun->isTemplate || !funcIsDirty(fun) ) return false;
                if ( !fun->body || !fun->body->rtti_isBlock() ) return false;
                dead.clear();
                analyzeDeadStores(fun, dead);
                return !dead.empty();
            }
            virtual bool canVisitStructure ( Structure * ) override { return false; }
            virtual bool canVisitStructureFieldInit ( Structure * ) override { return false; }
            virtual bool canVisitArgumentInit ( Function *, const VariablePtr &, Expression * ) override { return false; }
            virtual bool canVisitQuoteSubexpression ( ExprQuote * ) override { return false; }
            virtual bool canVisitGlobalVariable ( Variable * ) override { return false; }
            virtual bool canVisitEnumeration ( Enumeration * ) override { return false; }
            virtual ExpressionPtr visitBlockExpression ( ExprBlock * block, Expression * expr ) override {
                if ( dead.find(expr)!=dead.end() ) {
                    reportFolding();
                    return nullptr;
                }
                return Visitor::visitBlockExpression(block, expr);
            }
        };
    }

    // program

    bool Program::optimizationDeadStores(int32_t round) {
        if ( options.getBoolOption("disable_dse", policies.disable_dse) ) return false;
        checkSideEffects();
        EliminateDeadStores pass(round);
        visit(pass);
        return pass.didAnything();
    }
}
