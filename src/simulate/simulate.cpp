#include "daScript/misc/platform.h"

#include "daScript/simulate/simulate.h"
#include "daScript/simulate/runtime_string.h"
#include "daScript/simulate/debug_print.h"
#include <stdarg.h>

// this is here for the default implementation of to_out and to_err
#include <setjmp.h>

extern void os_debug_break();

namespace das
{
    DAS_THREAD_LOCAL Context * __restrict __context__;

    // this is here to occasionally investigate untyped evaluation paths
    #define WARN_SLOW_CAST(TYPE)
    // #define WARN_SLOW_CAST(TYPE)    DAS_ASSERTF(0, "internal perofrmance issue, casting eval to eval##TYPE" );

    bool SimNode::evalBool ( ) {
        WARN_SLOW_CAST(Bool);
        return cast<bool>::to(eval());
    }

    float SimNode::evalFloat ( ) {
        WARN_SLOW_CAST(Float);
        return cast<float>::to(eval());
    }

    double SimNode::evalDouble() {
        WARN_SLOW_CAST(Double);
        return cast<double>::to(eval());
    }

    int32_t SimNode::evalInt ( ) {
        WARN_SLOW_CAST(Int);
        return cast<int32_t>::to(eval());
    }

    uint32_t SimNode::evalUInt ( ) {
        WARN_SLOW_CAST(UInt);
        return cast<uint32_t>::to(eval());
    }

    int64_t SimNode::evalInt64 ( ) {
        WARN_SLOW_CAST(Int64);
        return cast<int64_t>::to(eval());
    }

    uint64_t SimNode::evalUInt64 ( ) {
        WARN_SLOW_CAST(UInt64);
        return cast<uint64_t>::to(eval());
    }

    char * SimNode::evalPtr ( ) {
        WARN_SLOW_CAST(Ptr);
        return cast<char *>::to(eval());
    }

    vec4f SimNode_DeleteStructPtr::eval ( ) {
        auto pStruct = (char **) subexpr->evalPtr();
        pStruct = pStruct + total - 1;
        for ( uint32_t i=0; i!=total; ++i, pStruct-- ) {
            if ( *pStruct ) {
                __context__->heap.free(*pStruct, structSize);
                *pStruct = nullptr;
            }
        }
        return v_zero();
    }

    vec4f SimNode_Swizzle::eval ( ) {
        union {
            vec4f   res;
            float   val[4];
        } R, S;
        S.res = value->eval();
        R.val[0] = S.val[fields[0]];
        R.val[1] = S.val[fields[1]];
        R.val[2] = S.val[fields[2]];
        R.val[3] = S.val[fields[3]];
        return R.res;
    }

    // SimNode_MakeBlock

    vec4f SimNode_MakeBlock::eval ( )  {
        Block * block = (Block *) ( __context__->stack.sp() + stackTop );
        block->stackOffset = __context__->stack.spi();
        block->argumentsOffset = argStackTop ? (__context__->stack.spi() + argStackTop) : 0;
        block->body = subexpr;
        block->functionArguments = __context__->abiArguments();
        return cast<Block *>::from(block);
    }

    // SimNode_Debug

    vec4f SimNode_Debug::eval ( ) {
        vec4f res = subexpr->eval();
        TextWriter ssw;
        if ( message ) ssw << message << " ";
        ssw << debug_type(typeInfo) << " = " << debug_value(res, typeInfo, PrintFlags::debugger)
            << " at " << debugInfo.describe() << "\n";
        __context__->to_out(ssw.str().c_str());
        return res;
    }

    // SimNode_Assert

    vec4f SimNode_Assert::eval ( ) {
        if ( !subexpr->evalBool() ) {
            string error_message = "assert failed";
            if ( message )
                error_message = error_message + ", " + message;
            string error = reportError(debugInfo, error_message );
            error = __context__->getStackWalk(false) + error;
            __context__->to_err(error.c_str());
            __context__->throw_error_at(debugInfo,"assert failed");
        }
        return v_zero();
    }

    // SimNode_TryCatch

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4611)
#endif

    vec4f SimNode_TryCatch::eval ( ) {
        auto aa = __context__->abiArg; auto acm = __context__->abiCMRES;
        char * EP, * SP;
        __context__->stack.watermark(EP,SP);
        #if DAS_ENABLE_EXCEPTIONS
            try {
                try_block->eval(context);
            } catch ( const dasException & ) {
                __context__->abiArg = aa;
                __context__->abiCMRES = acm;
                __context__->stack.pop(EP,SP);
                __context__->stopFlags &= ~(EvalFlags::stopForThrow | EvalFlags::stopForReturn | EvalFlags::stopForBreak);
                catch_block->eval(context);
            }
        #else
            jmp_buf ev;
            jmp_buf * JB = __context__->throwBuf;
            __context__->throwBuf = &ev;
            if ( !setjmp(ev) ) {
                try_block->eval();
            } else {
                __context__->throwBuf = JB;
                __context__->abiArg = aa;
                __context__->abiCMRES = acm;
                __context__->stack.pop(EP,SP);
                __context__->stopFlags &= ~(EvalFlags::stopForReturn | EvalFlags::stopForBreak);
                __context__->exception = nullptr;
                catch_block->eval();
            }
            __context__->throwBuf = JB;
        #endif
        return v_zero();
    }

#ifdef _MSC_VER
#pragma warning(pop)
#endif

    // SimNode_CopyRefValue

    vec4f SimNode_CopyRefValue::eval ( ) {
        auto pl = l->evalPtr();
        auto pr = r->evalPtr();
        memcpy ( pl, pr, size );
        return v_zero();
    }

    // SimNode_MoveRefValue

    vec4f SimNode_MoveRefValue::eval ( ) {
        auto pl = l->evalPtr();
        auto pr = r->evalPtr();
        memcpy ( pl, pr, size );
        memset ( pr, 0, size );
        return v_zero();
    }

    // SimNode_Block

    vec4f SimNode_Block::eval ( ) {
        for ( uint32_t i = 0; i!=total && !__context__->stopFlags; ) {
            list[i++]->eval();
        }
        evalFinal();
        return v_zero();
    }

    vec4f SimNode_ClosureBlock::eval ( ) {
        for ( uint32_t i = 0; i!=total && !__context__->stopFlags; ) {
            list[i++]->eval();
        }
        evalFinal();
        if ( __context__->stopFlags & EvalFlags::stopForReturn ) {
            __context__->stopFlags &= ~EvalFlags::stopForReturn;
            return __context__->abiResult();
        } else {
            if ( needResult ) __context__->throw_error_at(debugInfo,"end of block without return");
            return v_zero();
        }
    }

    // SimNode_Let

    vec4f SimNode_Let::eval ( ) {
        for ( uint32_t i = 0; i!=total && !__context__->stopFlags; ) {
            list[i++]->eval();
        }
        return subexpr ? subexpr->eval() : v_zero();
    }

    // SimNode_While

    vec4f SimNode_While::eval (  ) {
        SimNode ** __restrict tail = list + total;
        while ( cond->evalBool() && !__context__->stopFlags ) {
            for (SimNode ** __restrict body = list; body!=tail; ++body) {
                (*body)->eval();
                if (__context__->stopFlags) goto loopend;
            }
        }
    loopend:;
        evalFinal();
        __context__->stopFlags &= ~EvalFlags::stopForBreak;
        return v_zero();
    }

    // Return

    vec4f SimNode_Return::eval (  ) {
        if ( subexpr ) __context__->abiResult() = subexpr->eval();
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnConst::eval ( ) {
        __context__->abiResult() = value;
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnRefAndEval::eval ( ) {
        auto pl = __context__->abiCopyOrMoveResult();
        DAS_ASSERT(pl);
        auto pR = ((char **)(__context__->stack.sp() + stackTop));
        *pR = pl;
        subexpr->evalPtr();
        __context__->abiResult() = cast<char *>::from(pl);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnAndCopy::eval ( ) {
        auto pr = subexpr->evalPtr();
        auto pl = __context__->abiCopyOrMoveResult();
        DAS_ASSERT(pl);
        memcpy ( pl, pr, size);
        __context__->abiResult() = cast<char *>::from(pl);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnAndMove::eval ( ) {
        auto pr = subexpr->evalPtr();
        auto pl = __context__->abiCopyOrMoveResult();
        DAS_ASSERT(pl);
        memcpy ( pl, pr, size);
        memset ( pr, 0, size);
        __context__->abiResult() = cast<char *>::from(pl);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnReference::eval ( ) {
        char * ref = subexpr->evalPtr();
        if ( __context__->stack.bottom()<=ref && ref<__context__->stack.sp()) {
            __context__->throw_error_at(debugInfo,"reference bellow current function stack frame");
            return v_zero();
        }
#if DAS_ENABLE_STACK_WALK
        auto pp = (Prologue *) __context__->stack.sp();
        auto top = __context__->stack.sp() + pp->info->stackSize;
        if ( __context__->stack.sp()<=ref && ref<top ) {
            __context__->throw_error_at(debugInfo,"reference to current function stack frame");
            return v_zero();
        }
#endif
        __context__->abiResult() = cast<char *>::from(ref);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnRefAndEvalFromBlock::eval ( ) {
        auto ba = (BlockArguments *) ( __context__->stack.sp() + argStackTop );
        auto pl = ba->copyOrMoveResult;
        DAS_ASSERT(pl);
        auto pR = ((char **)(__context__->stack.sp() + stackTop));
        *pR = pl;
        subexpr->evalPtr();
        __context__->abiResult() = cast<char *>::from(pl);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnAndCopyFromBlock::eval ( ) {
        auto pr = subexpr->evalPtr();
        auto ba = (BlockArguments *) ( __context__->stack.sp() + argStackTop );
        auto pl = ba->copyOrMoveResult;
        memcpy ( pl, pr, size);
        __context__->abiResult() = cast<char *>::from(pl);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnAndMoveFromBlock::eval ( ) {
        auto pr = subexpr->evalPtr();
        auto ba = (BlockArguments *) ( __context__->stack.sp() + argStackTop );
        auto pl = ba->copyOrMoveResult;
        memcpy ( pl, pr, size);
        memset ( pr, 0, size);
        __context__->abiResult() = cast<char *>::from(pl);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    vec4f SimNode_ReturnReferenceFromBlock::eval ( ) {
        char * ref = subexpr->evalPtr();
        if ( __context__->stack.bottom()<=ref && ref<__context__->stack.ap() ) {
            __context__->throw_error_at(debugInfo,"reference bellow current call chain stack frame");
            return v_zero();
        }
        __context__->abiResult() = cast<char *>::from(ref);
        __context__->stopFlags |= EvalFlags::stopForReturn;
        return v_zero();
    }

    // Context

    Context::Context() : stack(16*1024) {
        code = make_shared<NodeAllocator>();
        debugInfo = make_shared<NodeAllocator>();
    }

    Context::Context(const Context & ctx) : stack(16*1024) {
        code = ctx.code;
        debugInfo = ctx.debugInfo;
        thisProgram = ctx.thisProgram;
        thisHelper = ctx.thisHelper;
        // globals
        globalsSize = ctx.globalsSize;
        globalInitStackSize = ctx.globalInitStackSize;
        globalVariables = ctx.globalVariables;
        totalVariables = ctx.totalVariables;
        if ( ctx.globals ) {
            globals = (char *) das_aligned_alloc16(globalsSize);
        }
        // functoins
        functions = ctx.functions;
        totalFunctions = ctx.totalFunctions;
        // now, make it good to go
        context_guard guard(*this);
        restart();
        runInitScript();
        restart();
    }

    Context::~Context() {
        if ( globals ) {
            das_aligned_free16(globals);
        }
    }

    void Context::runInitScript ( void ) {
        char * EP, *SP;
        if(!stack.push(globalInitStackSize,EP,SP)) {
            throw_error("stack overflow in the initialization script");
            return;
        }
        for ( int i=0; i!=totalVariables && !stopFlags; ++i ) {
            auto & pv = globalVariables[i];
            if ( pv.init ) {
                pv.init->eval();
            } else {
                memset ( globals + pv.offset, 0, pv.size );
            }
        }
        stack.pop(EP,SP);
    }

    SimFunction * Context::findFunction ( const char * name ) const {
        for ( int fni = 0; fni != totalFunctions; ++fni ) {
            if ( strcmp(functions[fni].name, name)==0 ) {
                return functions + fni;
            }
        }
        return nullptr;
    }

    int Context::findVariable ( const char * name ) const {
        for ( int vni = 0; vni != totalVariables; ++vni ) {
            if ( strcmp(globalVariables[vni].name, name)==0 ) {
                return vni;
            }
        }
        return -1;
    }

    void Context::stackWalk() {
        auto str = getStackWalk();
        to_out(str.c_str());
    }

    string Context::getStackWalk( bool args ) {
        TextWriter ssw;
    #if DAS_ENABLE_STACK_WALK
        ssw << "\nCALL STACK (sp=" << (stack.top() - stack.sp()) << "):\n";
        char * sp = stack.sp();
        while (  sp < stack.top() ) {
            Prologue * pp = (Prologue *) sp;
            if ( pp->line ) {
                ssw << pp->info->name << " at line " << pp->line << " (sp=" << (stack.top() - sp) << ")\n";
            } else {
                ssw << pp->info->name << "(sp=" << (stack.top() - sp) << ")\n";
            }
            if ( args ) {
                for ( uint32_t i = 0; i != pp->info->argsSize; ++i ) {
                    ssw << "\t" << pp->info->args[i]->name
                        << " : " << debug_type(pp->info->args[i])
                        << " = \t" << debug_value(pp->arguments[i], pp->info->args[i], PrintFlags::stackwalker) << "\n";
                }
            }
            sp += pp->info->stackSize;
        }
        ssw << "\n";
    #else
        ssw << "\nCALL STACK TRACKING DISABLED:\n\n";
    #endif
        return ssw.str();
    }

    void Context::breakPoint(int, int ) const {
        os_debug_break();
    }

    void Context::to_out ( const char * message ) {
		if (message) {
			fprintf(stdout, "%s", message);
			fflush(stdout);
		}
    }

    void Context::to_err ( const char * message ) {
		if (message) {
			fprintf(stderr, "%s", message);
			fflush(stderr);
		}
    }

    void Context::throw_error_at ( const LineInfo & at, const char * message, ... ) {
        const int PRINT_BUFFER_SIZE = 1024;
        char buffer[PRINT_BUFFER_SIZE];
        va_list args;
        va_start (args, message);
        vsnprintf (buffer,PRINT_BUFFER_SIZE,message, args);
        va_end (args);
        lastError = at.describe() + ": " + buffer;
        throw_error(lastError.c_str());
    }

    void Context::throw_error_ex ( const char * message, ... ) {
        const int PRINT_BUFFER_SIZE = 1024;
        char buffer[PRINT_BUFFER_SIZE];
        va_list args;
        va_start (args, message);
        vsnprintf (buffer,PRINT_BUFFER_SIZE,message, args);
        va_end (args);
        lastError = buffer;
        throw_error(lastError.c_str());
    }

    void Context::throw_error ( const char * message ) {
        exception = message;
#if DAS_ENABLE_EXCEPTIONS
        throw dasException(message ? message : "");
#else
        if ( throwBuf ) {
            longjmp(*throwBuf,1);
        } else {
            to_err("\nunhandled exception\n");
            if ( exception ) {
                to_err(exception);
                to_err("\n");
            }
            stackWalk();
            os_debug_break();
        }
#endif
    }

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4611)
#endif

    vec4f Context::evalWithCatch ( SimNode * node ) {
        auto aa = abiArg; auto acm = abiCMRES;
        char * EP, * SP;
        stack.watermark(EP,SP);
#if DAS_ENABLE_EXCEPTIONS
        try {
            return node->eval(*this);
        } catch ( const dasException & ) {
            /*
             to_err("\nunhandled exception\n");
             if ( exception ) {
             to_err(exception);
             to_err("\n");
             }
             stackWalk();
             */
            abiArg = aa; abiCMRES = acm;
            stack.pop(EP,SP);
            return v_zero();
        }
#else
        jmp_buf ev;
        jmp_buf * JB = throwBuf;
        throwBuf = &ev;
        if ( !setjmp(ev) ) {
            return node->eval();
        } else {
            abiArg = aa;
            abiCMRES = acm;
            stack.pop(EP,SP);
            throwBuf = JB;
            return v_zero();
        }
        throwBuf = JB;
#endif
    }

    vec4f Context::evalWithCatch ( SimFunction * fnPtr, vec4f * args, void * res ) {
        auto aa = abiArg; auto acm = abiCMRES;
        char * EP, * SP;
        stack.watermark(EP,SP);
#if DAS_ENABLE_EXCEPTIONS
        try {
            return call(fnPtr, args, res, 0);
        } catch ( const dasException & ) {
            /*
            to_err("\nunhandled exception\n");
            if ( exception ) {
                to_err(exception);
                to_err("\n");
            }
            stackWalk();
            */
            abiArg = aa; abiCMRES = acm;
            stack.pop(EP,SP);
            return v_zero();
        }
#else
        jmp_buf ev;
        jmp_buf * JB = throwBuf;
        throwBuf = &ev;
        if ( !setjmp(ev) ) {
            return callWithCopyOnReturn(fnPtr, args, res, 0);
        } else {
            abiArg = aa;
            abiCMRES = acm;
            stack.pop(EP,SP);
            throwBuf = JB;
            return v_zero();
        }
        throwBuf = JB;
#endif
    }

#ifdef _MSC_VER
#pragma warning(pop)
#endif
}
