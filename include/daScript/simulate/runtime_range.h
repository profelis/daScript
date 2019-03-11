#pragma once

#include "daScript/simulate/simulate.h"

namespace das
{
    struct RangeIterator : Iterator {
        virtual bool first ( IteratorContext & itc ) override;
        virtual bool next  ( IteratorContext & itc ) override;
        virtual void close ( IteratorContext & itc ) override;
        SimNode * subexpr;
    };

    struct SimNode_RangeIterator : SimNode, RangeIterator {
            SimNode_RangeIterator ( const LineInfo & at, SimNode * rng )
            : SimNode(at) { subexpr = rng; }
        virtual SimNode * visit ( SimVisitor & vis ) override;
        virtual vec4f eval ( ) override;
    };

    struct SimNode_ForRange : SimNode_ForBase  {
        SimNode_ForRange ( const LineInfo & at )
            : SimNode_ForBase(at) {}
        virtual SimNode * visit ( SimVisitor & vis ) override;
        virtual vec4f eval ( ) override;
    };

    struct SimNode_ForRangeNF : SimNode_ForBase  {
        SimNode_ForRangeNF ( const LineInfo & at )
            : SimNode_ForBase(at) {}
        virtual SimNode * visit ( SimVisitor & vis ) override;
        virtual vec4f eval ( ) override;
    };

    struct SimNode_ForRange1 : SimNode_ForBase  {
        SimNode_ForRange1 ( const LineInfo & at )
            : SimNode_ForBase(at) {}
        virtual SimNode * visit ( SimVisitor & vis ) override;
        virtual vec4f eval ( ) override;
    };

    struct SimNode_ForRangeNF1 : SimNode_ForBase  {
        SimNode_ForRangeNF1 ( const LineInfo & at )
            : SimNode_ForBase(at) {}
        virtual SimNode * visit ( SimVisitor & vis ) override;
        virtual vec4f eval ( ) override;
    };
}

