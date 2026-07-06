#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_visitor.h"
#include "daScript/ast/ast_bound_check_elision.h"

namespace das {

    namespace {
        // [hint(unsafe_range_check)] override: mark every access in the body (skips nested lambdas - separate scopes)
        struct MarkAllScan : Visitor {
            TextWriter * logs = nullptr;
            const char * fnName = "";
            int lam = 0;
            virtual void preVisit ( ExprMakeBlock * e ) override { Visitor::preVisit(e); lam++; }
            virtual ExpressionPtr visit ( ExprMakeBlock * e ) override { lam--; return Visitor::visit(e); }
            virtual void preVisit ( ExprAt * e ) override {
                Visitor::preVisit(e);
                if ( lam || e->noBoundCheck ) return;
                e->noBoundCheck = true;
                if ( logs ) *logs << "[bound-check-elision] " << fnName << ": " << e->at.describe()
                                  << " " << e->describe() << " (unsafe_range_check hint)\n";
            }
            static void mark ( Function * fn, TextWriter * logs ) {
                if ( !fn->body || !fn->body->rtti_isBlock() ) return;
                MarkAllScan s; s.logs = logs; s.fnName = fn->name.c_str(); fn->body->visit(s);
            }
        };
    }

    static bool hasUnsafeRangeCheckHint ( const FunctionPtr & fn ) {
        for ( auto & ann : fn->annotations )
            if ( ann->annotation->name=="hint" && ann->arguments.getBoolOption("unsafe_range_check", false) ) return true;
        return false;
    }

    void markNoBoundCheck ( Program * program, TextWriter & logs ) {
        if ( !program || !program->thisModule ) return;
        const bool doLog = program->options.getBoolOption("log_bound_check_elision", false);
        program->thisModule->functions.foreach([&](auto & fn){
            if ( hasUnsafeRangeCheckHint(fn) ) MarkAllScan::mark(fn, doLog ? &logs : nullptr);
        });
    }

}
