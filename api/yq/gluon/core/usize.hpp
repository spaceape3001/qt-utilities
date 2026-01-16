////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/shape/Size2.hpp>
#include <QSize>
#include <QSizeF>

namespace yq {
    inline QSize    qSize(const Size2U& v)
    {
        return QSize(v.x, v.y);
    }

    inline QSizeF   qSize(const Size2F& v)
    {
        return QSizeF(v.x, v.y);
    }

    inline QSizeF   qSize(const Size2D& v)
    {
        return QSizeF(v.x, v.y);
    }
}
