////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsTool.hpp>
#include <yq/meta/ObjectInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsToolInfo::Writer : public ObjectInfo::Writer<C> {
    public:
    
        Writer(GraphicsToolInfo* pInfo) : ObjectInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsToolInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsToolInfo* m_meta;
    };
}
