#include "daScript/misc/platform.h"

#include "daScript/simulate/runtime_range.h"

namespace das
{
    bool RangeIterator::first ( IteratorContext & itc ) {
        vec4f ll = subexpr->eval();
        range r = cast<range>::to(ll);  // does not matter if its range or urange, hence only one type
        itc.value    = cast<int32_t>::from(r.from);
        itc.range_to = r.to;
        return (r.from!=r.to);
    }

    bool RangeIterator::next  ( IteratorContext & itc ) {
        int32_t nextValue = cast<int32_t>::to(itc.value) + 1;
        itc.value = cast<int32_t>::from(nextValue);
        return (nextValue != itc.range_to);
    }

    void RangeIterator::close ( IteratorContext & ) {
    }

    vec4f SimNode_RangeIterator::eval ( ) {
        return cast<Iterator *>::from(static_cast<RangeIterator *>(this));
    }

    vec4f SimNode_ForRange::eval ( ) {
        vec4f ll = sources[0]->eval();
        range r = cast<range>::to(ll);
        int32_t * __restrict pi = (int32_t *)(__context__->stack.sp() + stackTop[0]);
        int32_t r_to = r.to;
        SimNode ** __restrict tail = list + total;
        for (int32_t i = r.from; i != r_to; ++i) {
            *pi = i;
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

    vec4f SimNode_ForRangeNF::eval ( ) {
        vec4f ll = sources[0]->eval();
        range r = cast<range>::to(ll);
        int32_t * __restrict pi = (int32_t *)(__context__->stack.sp() + stackTop[0]);
        int32_t r_to = r.to;
        SimNode ** __restrict tail = list + total;
        for (int32_t i = r.from; i != r_to; ++i) {
            *pi = i;
            for (SimNode ** __restrict body = list; body!=tail; ++body) {
                (*body)->eval();
            }
        }
        evalFinal();
        __context__->stopFlags &= ~EvalFlags::stopForBreak;
        return v_zero();
    }

    vec4f SimNode_ForRange1::eval ( ) {
        vec4f ll = sources[0]->eval();
        range r = cast<range>::to(ll);
        int32_t * __restrict pi = (int32_t *)(__context__->stack.sp() + stackTop[0]);
        int32_t count = r.to - r.from; // [0,3] 0,1,2
        auto i = r.from;
        SimNode * __restrict pbody = list[0];
        while ( count>=4 ) {
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
            count -= 4;
        }
        if ( count & 2 ) {
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
        }
        if ( count & 1 ) {
            *pi=i++; pbody->eval(); if ( __context__->stopFlags ) goto done;
        }
    done:;
        evalFinal();
        __context__->stopFlags &= ~EvalFlags::stopForBreak;
        return v_zero();
    }

    vec4f SimNode_ForRangeNF1::eval ( ) {
        vec4f ll = sources[0]->eval();
        range r = cast<range>::to(ll);
        int32_t * __restrict pi = (int32_t *)(__context__->stack.sp() + stackTop[0]);
        int32_t count = r.to - r.from; // [0,3] 0,1,2
        auto i = r.from;
        SimNode * __restrict pbody = list[0];
        while ( count>=4 ) {
            *pi=i++; pbody->eval();
            *pi=i++; pbody->eval();
            *pi=i++; pbody->eval();
            *pi=i++; pbody->eval();
            count -= 4;
        }
        if ( count & 2 ) {
            *pi=i++; pbody->eval();
            *pi=i++; pbody->eval();
        }
        if ( count & 1 ) {
            *pi=i++; pbody->eval();
        }
        evalFinal();
        __context__->stopFlags &= ~EvalFlags::stopForBreak;
        return v_zero();
    }
}
