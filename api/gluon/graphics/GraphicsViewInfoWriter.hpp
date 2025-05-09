////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsView.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsViewInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        Writer(GraphicsViewInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsViewInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsViewInfo* m_meta;
    };
}
