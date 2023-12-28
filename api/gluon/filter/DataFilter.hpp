////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <functional>

class QVariant;

namespace yq::gluon {

    

    using DataFilter    = std::function<bool(const QVariant&)>;
    
    DataFilter      operator&&(DataFilter&&, DataFilter&&);
    DataFilter      operator||(DataFilter&&, DataFilter&&);
    DataFilter      operator^(DataFilter&&, DataFilter&&);
    DataFilter      operator!(DataFilter&&);
}
