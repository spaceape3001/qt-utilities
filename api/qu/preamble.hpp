////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

namespace yq {
    template <typename T> class Ref;
}

namespace qu {
    using yq::Vector;
    using yq::Map;
    using yq::Set;
    using yq::Ref;

    struct IgCase;
    using StringMap             = Map<QString,QString,IgCase>;
    using StringSet             = Set<QString,IgCase>;
}
