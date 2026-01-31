////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "urect.hpp"

#include <yq/gluon/core/upoint.hpp>
#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Rectangle2.hpp>
#include <QRectF>

#include <yq/shape/AxBox2.hxx>

namespace yq {
    QRectF  qRect(const AxBox2D&bx)
    {
        return QRectF(bx.lo.x, bx.lo.y, bx.width(), bx.height());
    }
    
    QRectF  qRect(const AxBox2F&bx)
    {
        return QRectF(bx.lo.x, bx.lo.y, bx.width(), bx.height());
    }
    
    QRectF  qRect(const Rectangle2D&bx)
    {
        return QRectF(bx.position.x, bx.position.y, bx.size.x, bx.size.y);
    }
    
    QRectF  qRect(const Rectangle2F&bx)
    {
        return QRectF(bx.position.x, bx.position.y, bx.size.x, bx.size.y);
    }
}
