////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsView.hpp>
#include <gluon/core/WidgetQMetaWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsViewMeta::Writer : public WidgetQMeta::Writer<C> {
    public:
    
        Writer(GraphicsViewMeta* pInfo) : WidgetQMeta::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsViewMeta& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsViewMeta* m_meta;
    };
}
