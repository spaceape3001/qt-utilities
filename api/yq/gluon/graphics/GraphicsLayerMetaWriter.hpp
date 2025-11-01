////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsLayer.hpp>
#include <yq/gluon/core/ObjectQMetaWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsLayerMeta::Writer : public ObjectQMeta::Writer<C> {
    public:
    
        Writer(GraphicsLayerMeta* pInfo) : ObjectQMeta::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsLayerMeta& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsLayerMeta* m_meta;
    };
}
