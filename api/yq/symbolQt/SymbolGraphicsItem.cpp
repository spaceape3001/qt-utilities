////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>

#include "SymbolGraphicsItem.hpp"
#include "SymbolGraphicsItem.hxx"
#include "SGIBase.hpp"
#include "SGIText.hpp"

#include <yq/gluon/core/Logging.hpp>
#include <yq/gluon/core/ucolor.hpp>
#include <yq/gluon/core/upoint.hpp>
#include <yq/gluon/core/urect.hpp>
#include <yq/gluon/core/ustring.hpp>
#include <yq/net/Url.hpp>
#include <yq/symbol/Pin.hpp>
#include <yq/symbol/Shape.hpp>
#include <yq/symbol/Symbol.hpp>

#include <QBrush>
#include <QFont>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPen>

#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Circle2.hxx>
#include <yq/shape/Oval2.hxx>
#include <yq/shape/Polygon2.hxx>
#include <yq/shape/Polyline2.hxx>
#include <yq/shape/Segment2.hxx>
#include <yq/shape/Size2.hxx>
#include <yq/shape/Triangle2.hxx>
#include <yq/vector/Vector2.hxx>

namespace yq::gluon {

    SymbolGraphicsItem::SymbolGraphicsItem(QGraphicsItem*parent) : QGraphicsItemGroup(parent)
    {
    }
    
    SymbolGraphicsItem::~SymbolGraphicsItem()
    {
    }

    void    SymbolGraphicsItem::build(const Symbol&sym, float size)
    {
        using namespace yq::symbol;
        
        size *= sym.scale;
        
        auto makeFont = [&](const font_style_t& sty) -> QFont {
            return QFont();
        };
        
        auto makeBrush  = [&](const fill_style_t& sty) -> QBrush {
            if(sty.use != Tristate::Yes)
                return QBrush(Qt::NoBrush);
            if(sty.color.alpha < 0)
                return QBrush(Qt::white);
            return QBrush(qColor(sty.color));
        };
        
        auto makePen    = [&](const stroke_style_t & sty) -> QPen {
            if(sty.use == Tristate::No)
                return QPen(Qt::NoPen);
            if(sty.color.alpha < 0.)
                return QPen();
            
            QPen    pen(qColor(sty.color));
            pen.setWidthF(sty.width);
            return pen;
        };
        
        auto addMe  = [&](QGraphicsItem* gi, const style_t& sty) {
            if(!gi)
                return ;
        
            const auto& font       = (sty.font.use == Tristate::Inherit) ? sym.style.font : sty.font;
            const auto& fill       = (sty.fill.use == Tristate::Inherit) ? sym.style.fill : sty.fill;
            const auto& stroke     = (sty.stroke.use == Tristate::Inherit) ? sym.style.stroke : sty.stroke;
            
            if(QAbstractGraphicsShapeItem*gsi   = dynamic_cast<QAbstractGraphicsShapeItem*>(gi)){
                gsi -> setPen(makePen(stroke));
                gsi -> setBrush(makeBrush(fill));
            }
            if(QGraphicsLineItem* gli = dynamic_cast<QGraphicsLineItem*>(gi)){
                gli -> setPen(makePen(stroke));
            }
            if(QGraphicsSimpleTextItem* sti = dynamic_cast<QGraphicsSimpleTextItem*>(gi)){
                sti -> setFont(makeFont(font));
            }
            
            if(SGIBase* sb = dynamic_cast<SGIBase*>(gi))
                sb -> adjust();

            gi->setParentItem(this);
            addToGroup(gi);
            
            //  others....
            
        };
        
        AxBox2F     bb  = ZERO;

        for(auto& sh : sym.shape){
            QGraphicsItem*  gi = nullptr;
            if(const auto* p = std::get_if<AxBox2F>(&sh.primitive)){
                AxBox2F sz2 = size * *p;
                bb |= sz2;
                gi  = new SGIAdapter<QGraphicsRectItem>(qRect(sz2));
            }
            if(const auto* p = std::get_if<Circle2F>(&sh.primitive)){
                AxBox2F sz2 = size * p->bounds();
                bb |= sz2;
                gi  = new SGIAdapter<QGraphicsEllipseItem>(qRect(sz2));
            }
            if(const auto* p = std::get_if<Oval2F>(&sh.primitive)){
                AxBox2F sz2 = size * p->bounds();
                bb |= sz2;
                gi  = new SGIAdapter<QGraphicsEllipseItem>(qRect(sz2));
            }
            if(const auto* p = std::get_if<Polygon2F>(&sh.primitive)){
                QPolygonF   poly;
                for(size_t n=0;n<p->vertex.size();++n){
                    Vector2F    pt = size * p->vertex[n];
                    bb |= pt;
                    poly << qPoint(pt);
                }
                gi = new QGraphicsPolygonItem(poly);
            }
            if(const auto* p = std::get_if<Polyline2F>(&sh.primitive)){
                QPainterPath    path;
                for(size_t n=0;n<p->vertex.size();++n){
                    Vector2F    pt = size * p->vertex[n];
                    bb |= pt;
                    if(!n){
                        path.moveTo(qPoint(pt));
                    } else {
                        path.lineTo(qPoint(pt));
                    }
                }
                gi  = new SGIAdapter<QGraphicsPathItem>(path);
            }
            if(const auto* p = std::get_if<Segment2F>(&sh.primitive)){
                Segment2F   expanded    = size * *p;
                bb |= expanded.a;
                bb |= expanded.b;
                gi  = new SGIAdapter<QGraphicsLineItem>(QLineF(qPoint(expanded.a), qPoint(expanded.b)));
            }
            if(const auto* p = std::get_if<Triangle2F>(&sh.primitive)){
                Triangle2F  t   = size * *p;
                QPolygonF    poly;
                bb |= t.a;
                bb |= t.b;
                bb |= t.c;
                poly << qPoint(t.a);
                poly << qPoint(t.b);
                poly << qPoint(t.c);
                gi = new QGraphicsPolygonItem(poly);
            }
            if(const auto* p = std::get_if<image_t>(&sh.primitive)){
            }
            if(const auto* p = std::get_if<text_t>(&sh.primitive)){
                SGIText*    sti = new SGIText(*p, size);
                //m_textByKey[sh.key]  = sti;
                m_texts.push_back(sti);
                gi = sti;
            }
            
            addMe(gi, sh.style);
        }

        m_symbox        = qRect(bb);
        
        auto makePin    = [&](PinData& pd, const Vector2F& pt) -> QGraphicsItem* {
            pd.point        = qPoint(size * pt);

            // be configurable (later)
            PinShape    ps  = pd.pin.shape;
            if(ps == PinShape::Default){
                switch(pd.pin.flow){
                case PinFlow::Bi:
                    ps      = PinShape::Circle;
                    break;
                case PinFlow::In:
                case PinFlow::Out:
                    ps      = PinShape::Triangle;
                    break;
                case PinFlow::NC:
                    ps      = PinShape::None;
                    break;
                }
            } 
            
            Vector2F    hfz = size * (Vector2F) pd.pin.size;
            Vector2F    hpt = size * pt;
            pd.bounds       = AxBox2F(SORT, hpt - hfz, hpt + hfz);
            
            auto proj   = [&](const Vector2F& v) -> Vector2F
            {
                if(v == ZERO)
                    return hpt;
                return hpt + hfz.emul(v);
            };

            if(ps == PinShape::None)    // legal, no marked pin
                return nullptr;

            switch(ps){
            case PinShape::Circle:
            case PinShape::Oval:
                return new QGraphicsEllipseItem(qRect(pd.bounds));
            case PinShape::Rectangle:
                return new QGraphicsRectItem(qRect(pd.bounds));
            case PinShape::Diamond:
                {
                    QPolygonF   poly;
                    poly << QPointF( pd.bounds.lo.x, hpt.y );
                    poly << QPointF( hpt.x, pd.bounds.hi.y );
                    poly << QPointF( pd.bounds.hi.x, hpt.y );
                    poly << QPointF( hpt.x, pd.bounds.lo.y );
                    return new QGraphicsPolygonItem(poly);
                }
                break;
            case PinShape::Triangle:
                {
                    QPolygonF   poly;
                    if(pd.pin.flow == PinFlow::In){
                        poly << qPoint(proj({  pd.pin.direction.x, -pd.pin.direction.y}));
                        poly << qPoint(proj({  pd.pin.direction.y,  pd.pin.direction.x+pd.pin.direction.y}));
                        poly << qPoint(proj({ -pd.pin.direction.y,  pd.pin.direction.x+pd.pin.direction.y}));
                    } else {
                        poly << qPoint(proj({  pd.pin.direction.x,  pd.pin.direction.y}));
                        poly << qPoint(proj({  pd.pin.direction.y, -pd.pin.direction.x-pd.pin.direction.y}));
                        poly << qPoint(proj({ -pd.pin.direction.y, -pd.pin.direction.x-pd.pin.direction.y}));
                    }
                    
                    
                    return new QGraphicsPolygonItem(poly);
                }
                break;
            default:
                return nullptr;
            }
        };
        
        for(auto& pi : sym.pin){
            PinData     pd{pi};
            pd.item     = makePin(pd, pi.position);
            if(pd.item)
                addMe(pd.item, pi.style);
            m_pins.push_back(pd);
        }
        #if 0
            // when we have these....
        for(auto& pi : sym.pins){
            Vector2F  sz  = (Vector2F)(size * pi.size);
        }
        #endif
        
        //m_expanded  = qRect(bb);
        
        //  and metrics
    }

    void     SymbolGraphicsItem::setSymbol(SymbolCPtr sym)
    {
        m_symbol    = sym;
    }

    void     SymbolGraphicsItem::setSymSize(double v)
    {
        m_size          = v;
    }

    void     SymbolGraphicsItem::setTransform(SymTransform v)
    {
        m_transform     = v;
        m_transformFN   = nullptr;
    }
}

#include "SGIText.ipp"
