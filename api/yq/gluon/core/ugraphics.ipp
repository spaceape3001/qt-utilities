////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ugraphics.hpp"

#include <QGraphicsItem>
#include <QPointF>
#include <QRectF>

namespace yq {
    QRectF   qBoundingRect(const QGraphicsItem& item)
    {
        return item.mapToScene(item.boundingRect()).boundingRect();
    }

    QPointF qCenterPoint(const QGraphicsItem&item)
    {
        return item.mapToScene(item.boundingRect().center());
    }
}
