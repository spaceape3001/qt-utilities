////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <yq/meta/MetaBinder.hpp>
#include <QMetaType>

namespace yq::gluon {
    enum class GraphicsVisibility : uint8_t {
        Auto,
        Inherit = Auto,
        Hidden,
        Background,
        Show = Background,
        Items,
        Interactive = Items,
        Foreground
    };
    
    using GraphicsVisibilityFlags  = Flags<GraphicsVisibility, uint8_t>;
}

YQ_TYPE_DECLARE(yq::gluon::GraphicsVisibility)
YQ_TYPE_DECLARE(yq::gluon::GraphicsVisibilityFlags)
Q_DECLARE_METATYPE(yq::gluon::GraphicsVisibility)
Q_DECLARE_METATYPE(yq::gluon::GraphicsVisibilityFlags)
