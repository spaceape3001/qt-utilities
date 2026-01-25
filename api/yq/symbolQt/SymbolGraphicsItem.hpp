////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsItemGroup>
#include <yq/typedef/symbol.hpp>

namespace yq::gluon {
    class SymbolGraphicsItem : public QGraphicsItemGroup {
    public:
        SymbolGraphicsItem(QGraphicsItem*parent=nullptr);
        virtual ~SymbolGraphicsItem();
        
        void    build(const Symbol&, float size=64.f);
    };
}
