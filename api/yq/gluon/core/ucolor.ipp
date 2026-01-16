////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ucolor.hpp"

namespace yq {
    QColor          qColor(const RGBA4F&v)
    {
        QColor ret;
        ret.setRgbF(v.red, v.green, v.blue, v.alpha);
        return ret;
    }

    QColor          qColor(const RGB3F&v)
    {
        QColor ret;
        ret.setRgbF(v.red, v.green, v.blue);
        return ret;
    }
}
