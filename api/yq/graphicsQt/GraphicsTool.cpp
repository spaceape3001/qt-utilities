////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsTool.hpp"
#include "GraphicsToolMetaWriter.hpp"
#include "GraphicsScene.hpp"
#include "GraphicsView.hpp"
#include <QCursor>
#include <QIcon>

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsTool)

namespace yq::gluon {
    struct GraphicsToolMeta::Repo {
        MetaLookup<GraphicsToolMeta> all;
    };
    
    GraphicsToolMeta::Repo& GraphicsToolMeta::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    const GraphicsToolMeta* GraphicsToolMeta::find(std::string_view k)
    {
        return repo().all.find(k);
    }

    GraphicsToolMeta::GraphicsToolMeta(std::string_view zName, ObjectQMeta& base, const std::source_location& sl) :
        ObjectQMeta(zName, base, sl)
    {
        repo().all << this;
    }
    
    GraphicsToolMeta::~GraphicsToolMeta()
    {
    }
        
    ///////////////////////////////////////////////////////////////////////////

    void GraphicsTool::init_meta()
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
        return const_cast<GraphicsView*>(m_view)->scene();
    }
    
    GraphicsView*   GraphicsTool::view() const
    {
        return const_cast<GraphicsView*>(m_view);
    }
}

#include "moc_GraphicsTool.cpp"
