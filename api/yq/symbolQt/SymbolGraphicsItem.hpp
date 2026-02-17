////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsItemGroup>
#include <yq/core/Ref.hpp>
#include <yq/symbol/transform.hpp>
#include <yq/typedef/symbol.hpp>

namespace yq::gluon {
    class SGIText;
    
    using SymTransform = symbol::TransformMode;
    
    class SymbolGraphicsItem : public QGraphicsItemGroup {
    public:
        SymbolGraphicsItem(QGraphicsItem*parent=nullptr);
        virtual ~SymbolGraphicsItem();
        
        void    build(const Symbol&, float size=64.f);

        struct PinData;
        
        const auto&         pins() const { return m_pins; }
        const auto&         texts() const { return m_texts; }
        const QRectF&       symbox() const { return m_symbox; }
        
        //  some data... (attachment points/text here)
        //  transform to go here too...
        
        const auto&         symbol() const { return m_symbol; }
        void                setSymbol(SymbolCPtr);
        
        double              symSize() const { return m_size; }
        void                setSymSize(double);
        
        SymTransform        transform() const { return m_transform; }
        void                setTransform(SymTransform);
        
    private:
    
        std::vector<SGIText*>   m_texts;
        std::vector<PinData>    m_pins;
        QRectF                  m_symbox;
        double                  m_size          = 64.;
        SymTransform            m_transform     = SymTransform::IDENTITY;
        SymbolCPtr              m_symbol;
        uint64_t                m_symID         = 0ULL;
        symbol::FNTransform     m_transformFN   = nullptr;
    };
}
