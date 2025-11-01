////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsScene.hpp>
#include <gluon/core/ObjectQMetaWriter.hpp>

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
