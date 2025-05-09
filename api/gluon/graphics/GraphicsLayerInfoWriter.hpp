////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsLayer.hpp>
#include <gluon/core/ObjectQInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsLayerInfo::Writer : public ObjectQInfo::Writer<C> {
    public:
    
        Writer(GraphicsLayerInfo* pInfo) : ObjectQInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsLayerInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsLayerInfo* m_meta;
    };
}
