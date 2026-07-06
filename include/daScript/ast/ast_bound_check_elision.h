#pragma once

#include "daScript/ast/ast.h"

namespace das {

    // Mark accesses noBoundCheck. Honors the [hint(unsafe_range_check)] manual override (the same hint the JIT reads).
    void markNoBoundCheck ( Program * program, TextWriter & logs );

}
