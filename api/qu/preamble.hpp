////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

namespace qu {
    using yq::Vector;
    using yq::Map;
    using yq::Set;

    struct IgCase;
    using StringMap             = Map<QString,QString,IgCase>;
    using StringSet             = Set<QString,IgCase>;
}
