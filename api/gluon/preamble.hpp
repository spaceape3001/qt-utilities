////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

class QString;

namespace yq {}

namespace yq::gluon {
    struct IgCaseQ;
    
    using QStringMap            = Map<QString,QString,IgCaseQ>;
    using QStringSet            = Set<QString,IgCaseQ>;
}

