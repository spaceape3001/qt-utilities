////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsLayer.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsLayerInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        Writer(GraphicsLayerInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsLayerInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsLayerInfo* m_meta;
    };
}
