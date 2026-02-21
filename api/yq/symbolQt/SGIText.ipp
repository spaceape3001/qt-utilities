////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SGIText.hpp"
#include <yq/gluon/core/ustring.hpp>
#include <yq/symbol/Shape.hpp>

namespace yq::gluon {
    SGIText::SGIText(const symbol::text_t& txt, const SGITextOptions& opts) : adapter_t(), 
        m_text(txt), m_scale(opts.scale)
    {
        if(opts.text.isEmpty()){
            setText(qString(txt.text));
        } else {
            setText(opts.text);
        }
    }
    
    SGIText::~SGIText() {}

    void SGIText::adjust() 
    {
        QRectF  bb  = boundingRect();
        QPointF pp  = pos();
        
        double  x   = pp.x();
        double  y   = pp.y();

        double  w   = bb.width();
        double  h   = bb.height();
        Vector2F    point   = m_scale * m_text.position;
        
        switch(m_text.halign){
        case symbol::HAlign::Left:
            x       = point.x;
            break;
        case symbol::HAlign::Center:
            x       = point.x - 0.5 * w;
            break;
        case symbol::HAlign::Right:
            x       = point.x - w;
            break;
        }

        switch(m_text.valign){
        case symbol::VAlign::Top:
            y       = point.y;
            break;
        case symbol::VAlign::Middle:
            y       = point.y - 0.5 * h;
            break;
        case symbol::VAlign::Bottom:
            y       = point.y - h;
            break;
        }
        
        setPos(QPointF(x,y));
    }
}
