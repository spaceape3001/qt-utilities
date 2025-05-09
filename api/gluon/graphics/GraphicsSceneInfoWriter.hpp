////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsScene.hpp>
#include <gluon/core/ObjectQInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsSceneInfo::Writer : public ObjectQInfo::Writer<C> {
    public:
    
        Writer(GraphicsSceneInfo* pInfo) : ObjectQInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsSceneInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsSceneInfo* m_meta;
    };
}
