////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsScene.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsSceneInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        Writer(GraphicsSceneInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsSceneInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsSceneInfo* m_meta;
    };
}
