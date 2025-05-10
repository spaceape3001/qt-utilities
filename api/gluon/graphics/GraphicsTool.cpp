////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsTool.hpp"
#include "GraphicsToolWriter.hpp"
#include "GraphicsScene.hpp"
#include "GraphicsView.hpp"
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

    bool    GraphicsTool::active() const
    {
        return static_cast<bool>(m_view);
    }

    QCursor GraphicsTool::cursor() const
    {
        return QCursor();
    }
    
    QIcon   GraphicsTool::icon() const
    {
        return QIcon();
    }

    GraphicsScene*  GraphicsTool::scene() const
    {
        if(!m_view) 
            return nullptr;
        return const_cast<GraphicsView*>(m_view->scene());
    }
    
    GraphicsView*   GraphicsTool::view() const
    {
        return const_cast<GraphicsView*>(m_view);
    }
}

#include "moc_GraphicsTool.cpp"
