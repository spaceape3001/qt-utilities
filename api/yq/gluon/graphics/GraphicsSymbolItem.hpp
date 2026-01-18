////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsItemGroup>
#include <yq/typedef/symbol.hpp>

namespace yq::gluon {
    class GraphicsSymbolItem : public QGraphicsItemGroup {
    public:
        GraphicsSymbolItem(QGraphicsItem*parent=nullptr);
        virtual ~GraphicsSymbolItem();
        
        void    build(const Symbol&, float size=64.f);
    };
}
