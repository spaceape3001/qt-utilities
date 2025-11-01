////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsScene.hpp>
#include <yq/gluon/core/ObjectQMetaWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsSceneMeta::Writer : public ObjectQMeta::Writer<C> {
    public:
    
        Writer(GraphicsSceneMeta* pInfo) : ObjectQMeta::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsSceneMeta& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsSceneMeta* m_meta;
    };
}
