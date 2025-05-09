////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graphics/GraphicsTool.hpp>
#include <gluon/core/ObjectQInfoWriter.hpp>

namespace yq::gluon {
    
    /*! \brief Writer of trigger information
    */
    template <typename C>
    class GraphicsToolInfo::Writer : public ObjectQInfo::Writer<C> {
    public:
    
        Writer(GraphicsToolInfo* pInfo) : ObjectQInfo::Writer<C>(pInfo), m_meta(pInfo)
        {
        }
        
        Writer(GraphicsToolInfo& pInfo) : Writer(&pInfo)
        {
        }

    private:
        GraphicsToolInfo* m_meta;
    };
}
