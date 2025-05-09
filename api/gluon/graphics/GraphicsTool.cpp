////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsTool.hpp"
#include "GraphicsToolWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsTool)

namespace yq::gluon {

    GraphicsToolInfo::GraphicsToolInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
    }
    
    GraphicsToolInfo::~GraphicsToolInfo()
    {
    }
        
    ///////////////////////////////////////////////////////////////////////////

    void GraphicsTool::init_info()
    {
        auto w = writer<GraphicsTool>();
        w.description("Graphics Tool");
    }
        
    GraphicsTool::GraphicsTool()
    {
    }
    
    GraphicsTool::~GraphicsTool()
    {
    }
}

#include "moc_GraphicsTool.cpp"
