////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/shape/AxBox2.hpp>
#include <yq/symbol/Pin.hpp>
#include <yq/symbolQt/SymbolGraphicsItem.hpp>

namespace yq::gluon {
    struct SymbolGraphicsItem::PinData {
        const symbol::PinBase&  pin;
        QGraphicsItem*          item    = nullptr;
        QPointF                 point;
        AxBox2F                 bounds  = {};
    };
}
