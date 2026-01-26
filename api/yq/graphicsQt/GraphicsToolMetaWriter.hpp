////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>
#include <yq/gluon/core/ObjectQMetaWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsToolMeta::Writer : public ObjectQMeta::Writer<C> {
    public:
    
        Writer(GraphicsToolMeta* pInfo) : ObjectQMeta::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsToolMeta& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsToolMeta* m_meta;
    };
}
