////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>

#include "GraphicsSymbolItem.hpp"
#include <yq/gluon/core/Logging.hpp>
#include <yq/symbol/Pin.hpp>
#include <yq/symbol/Shape.hpp>
#include <yq/symbol/Symbol.hpp>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include <yq/net/Url.hpp>
#include <yq/shape/AxBox2.hxx>
#include <yq/shape/Circle2.hxx>
#include <yq/shape/Oval2.hxx>

namespace yq::gluon {
    GraphicsSymbolItem::GraphicsSymbolItem(QGraphicsItem*parent) : QGraphicsItemGroup(parent)
    {
    }
    
    GraphicsSymbolItem::~GraphicsSymbolItem()
    {
    }

    static QRectF qRectF(const AxBox2F& bx)
    {
        return QRectF(bx.lo.x, bx.lo.y, bx.width(), bx.height());
    }

    void    GraphicsSymbolItem::build(const Symbol&sym, float size)
    {
        for(auto& sh : sym.shape){
            QGraphicsItem*  gi = nullptr;
            if(const auto* p = std::get_if<AxBox2F>(&sh.primitive)){
                gi  = new QGraphicsRectItem(qRectF(size * *p));
            }
            if(const auto* p = std::get_if<Circle2F>(&sh.primitive)){
                gi  = new QGraphicsEllipseItem(qRectF(size * p->bounds()));
            }
            if(const auto* p = std::get_if<Oval2F>(&sh.primitive)){
                gi  = new QGraphicsEllipseItem(qRectF(size * p->bounds()));
            }
            if(gi){
                addToGroup(gi);
            }
        }
        for(auto& sh : sym.pin){
        }
        for(auto& sh : sym.pins){
        }
    }
}
