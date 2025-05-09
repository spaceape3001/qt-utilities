////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsTool.hpp"
#include "GraphicsToolWriter.hpp"
#include <QCursor>
#include <QIcon>

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsTool)

namespace yq::gluon {

    GraphicsToolInfo::GraphicsToolInfo(std::string_view zName, ObjectQInfo& base, const std::source_location& sl) :
        ObjectQInfo(zName, base, sl)
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

    QCursor GraphicsTool::cursor() const
    {
        return QCursor();
    }
    
    QIcon   GraphicsTool::icon() const
    {
        return QIcon();
    }
}

#include "moc_GraphicsTool.cpp"
