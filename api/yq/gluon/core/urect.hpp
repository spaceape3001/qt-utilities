////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/typedef/axbox2.hpp>
#include <yq/typedef/rectangle2.hpp>

class QRectF;

namespace yq {
    QRectF  qRect(const AxBox2D&);
    QRectF  qRect(const AxBox2F&);
    QRectF  qRect(const Rectangle2D&);
    QRectF  qRect(const Rectangle2F&);
}
