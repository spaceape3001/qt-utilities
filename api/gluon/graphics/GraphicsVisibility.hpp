////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Enum.hpp>
#include <yq/core/Flag.hpp>
#include <yq/meta/InfoBinder.hpp>
#include <QMetaType>

namespace yq::gluon {
    YQ_ENUM(GraphicsVisibility, ,
        Auto,
        Inherit = Auto,
        Hidden,
        Background,
        Show = Background,
        Items,
        Interactive = Items,
        Foreground
    );
    
    using GraphicsVisibilityFlags  = Flag<GraphicsVisibility>;
}

YQ_TYPE_DECLARE(yq::gluon::GraphicsVisibility)
YQ_TYPE_DECLARE(yq::gluon::GraphicsVisibilityFlags)
Q_DECLARE_METATYPE(yq::gluon::GraphicsVisibility)
Q_DECLARE_METATYPE(yq::gluon::GraphicsVisibilityFlags)
