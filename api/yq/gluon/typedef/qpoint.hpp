////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <yq/core/Expect.hpp>

class QPoint;
class QPointF;

namespace yq {
    template <typename> struct Result;

    using qpoint_r  = Result<QPoint>;
    using qpoint_x  = Expect<QPoint>;

    using qpointf_r = Result<QPointF>;
    using qpointf_x = Expect<QPointF>;
}
