////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>

class QMetaType;
class QVariant;

namespace yq {
    class Any;
}

namespace yq::gluon {
    typedef QVariant (*AnyToQVariantFN)(const Any&);
    typedef Any      (*QVariantToAnyFN)(const QVariant&);
}
