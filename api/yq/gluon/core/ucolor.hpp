////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/color/RGB.hpp>
#include <yq/color/RGBA.hpp>
#include <QColor>

namespace yq {

    inline QColor   qColor(const RGB3U8&v)
    {
        return QColor((int) v.red, (int) v.green, (int) v.blue);
    }
    
    inline QColor   qColor(const RGBA4U8&v)
    {
        return QColor((int) v.red, (int) v.green, (int) v.blue, (int) v.alpha);
    }
    
    QColor  qColor(const RGBA4F&);
    QColor  qColor(const RGB3F&);
}

