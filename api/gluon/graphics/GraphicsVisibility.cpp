////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsVisibility.hpp"
#include <yq/meta/Init.hpp>

YQ_TYPE_IMPLEMENT(yq::gluon::GraphicsVisibility)
YQ_TYPE_IMPLEMENT(yq::gluon::GraphicsVisibilityFlags)

namespace {
    void    reg_visibility()
    {
        using namespace yq;
        using namespace yq::gluon;
        
        {
            auto w = writer<GraphicsVisibility>();
            w.description("Visibility state enumeration");
        }

        {
            auto w = writer<GraphicsVisibilityFlags>();
            w.description("Flags of visibility state enumeration");
        }
        
        qRegisterMetaType<GraphicsVisibility>();
        qRegisterMetaType<GraphicsVisibilityFlags>();
    }
    
    YQ_INVOKE(reg_visibility();)
}
