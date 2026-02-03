////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsItemGroup>
#include <yq/typedef/symbol.hpp>

namespace yq::gluon {
    class SGIText;
    
    class SymbolGraphicsItem : public QGraphicsItemGroup {
    public:
        SymbolGraphicsItem(QGraphicsItem*parent=nullptr);
        virtual ~SymbolGraphicsItem();
        
        void    build(const Symbol&, float size=64.f);

        struct PinData;
        
        const auto&         pins() const { return m_pins; }
        const auto&         texts() const { return m_texts; }
        const QRectF&       symbox() const { return m_symbox; }
        
        // some data... (attachment points/text here)
    private:
    
        std::vector<SGIText*>           m_texts;
        std::vector<PinData>            m_pins;
        QRectF                          m_symbox;
    };
}
