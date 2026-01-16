////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/vector/Vector2.hpp>
#include <QPoint>
#include <QPointF>

namespace yq {
    inline QPoint  qPoint(const Vector2I&v)
    {
        return QPoint(v.x, v.y);
    }

    inline QPointF qPoint(const Vector2F&v)
    {
        return QPointF(v.x, v.y);
    }

    inline QPointF qPoint(const Vector2D&v)
    {
        return QPointF(v.x, v.y);
    }
}
