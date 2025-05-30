////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <concepts>

namespace yq::gluon {
    class Dock;
    class DockInfo;
    template <class D>
    concept SomeDock        = std::derived_from<D,Dock>;
}
