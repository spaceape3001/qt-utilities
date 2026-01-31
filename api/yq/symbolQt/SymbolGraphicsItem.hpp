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
        
        
        const QRectF&       symbox() const { return m_symbox; }
        
        // some data... (attachment points/text here)
    private:
        struct PinData;
    
        std::map<std::string, SGIText*> m_textByKey;
        std::vector<SGIText*>           m_texts;
        std::map<std::string, PinData>  m_pins;
        QRectF                          m_symbox;
    };
}
