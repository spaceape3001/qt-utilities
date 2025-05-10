////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsView.hpp>
#include <gluon/core/WidgetQInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsViewInfo::Writer : public WidgetQInfo::Writer<C> {
    public:
    
        Writer(GraphicsViewInfo* pInfo) : WidgetQInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsViewInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsViewInfo* m_meta;
    };
}
