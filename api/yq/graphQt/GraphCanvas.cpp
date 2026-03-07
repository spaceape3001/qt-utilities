////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphCanvas.hpp"
#include "GraphScene.hpp"
#include "GraphView.hpp"
#include "GraphItem.hpp"

#include <yq/container/vector_utils.hpp>
#include <yq/text/match.hpp>
#include <yq/graph/GDocument.hpp>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsItem>


namespace yq::gluon {
    static std::atomic<unsigned>    gCanvasNum{1};

    GraphCanvas::GraphCanvas(QWidget*parent) :
        GraphicsCanvas(new GraphView(new GraphScene()), parent),
        m_number(gCanvasNum++)
    {
        m_view      = (GraphView*) GraphicsCanvas::view();
        m_scene     = (GraphScene*) GraphicsCanvas::scene();
        m_scene -> setParent(this);
        m_scene -> setSceneRect(QRectF(0,0,2048,2048));
        featureEnable(Feature::SelectEffect);
    }
    
    GraphCanvas::~GraphCanvas()
    {
    }

    void        GraphCanvas::clear()
    {
        m_scene -> clear();
        m_graph = {};
    }

    void        GraphCanvas::deleteSelection()
    {
        std::vector<gid_t>  gids    = selectedIDs();
        if(gids.empty())
            return ;
        if(!m_graph.document())
            return;
        
        gids    = m_graph.document() -> affected(gids);
        m_graph.document() -> erase(gids);
        hideAll(gids);
    }

    GDocumentPtr  GraphCanvas::document() const
    {
        return const_cast<GraphCanvas*>(this)->m_graph.document();
    }

    std::filesystem::path   GraphCanvas::dirpath() const
    {
        return filepath().parent_path();
    }
    
    QString                 GraphCanvas::dirname() const
    {
        return QString::fromStdString(dirpath().string());
    }

    void                  GraphCanvas::doubleClick(GBase gb)
    {
        if(gb.document() != m_graph.document())
            return ;
        doubleClicked(gb.id());
    }

    std::filesystem::path GraphCanvas::filepath() const
    {
        Url u   = url();
    
        if(!is_similar(u.scheme, "file"))
            return {};
        if(!u.fragment.empty())
            return {};
        if(!u.query.empty())
            return {};
        return u.path;
    }

    QString GraphCanvas::filename() const
    {
        return QString::fromStdString(filepath().string());
    }

    GGraph      GraphCanvas::get() const
    {
        return m_graph;
    }

    void    GraphCanvas::hideAll(std::span<const gid_t> gids)
    {
        if(!m_scene)
            return;
        for(gid_t g : gids){
            GraphItem* gi = m_scene->item(g);
            if(!gi)
                continue;
            hide(gi->qItem());
        }
        m_scene -> updateAll();
    }

    void    GraphCanvas::refresh()
    {
        m_scene -> updateAll();
    }

    void    GraphCanvas::rightClick(GBase gb)
    {
        if(gb.document() != m_graph.document())
            return ;
        contextRequest(gb.id());
    }
    
    std::vector<gid_t>           GraphCanvas::selectedIDs() const
    {
        std::set<gid_t>  ret;
        for(const QGraphicsItem* qi : selected()){
            const GraphItem* gi = dynamic_cast<const GraphItem*>(qi);
            if(!gi)
                continue;
            gid_t   id  = gi->id();
            if(!id)
                continue;
            ret.insert(id);
        }
        return make_vector(ret);
    }

    void                    GraphCanvas::set(GGraph gg, const Url& u)
    {
        m_scene -> set(gg);
        m_graph     = gg;
        
        if(!u.empty()){
            m_url   = u;
        } else if(auto doc    = m_graph.document()){
            m_url   = doc->url();
        } else
            m_url   = {};
        
        updateTitle();
    }

    void    GraphCanvas::showAll(std::span<const gid_t> gids)
    {
        if(!m_scene)
            return;
        for(gid_t g : gids){
            GraphItem* gi = m_scene->item(g);
            if(!gi)
                continue;
            show(gi->qItem());
        }
        m_scene -> updateAll();
    }

    void    GraphCanvas::updateTitle()
    {
        std::string s = to_string(url());
        if(s.empty()){
            setWindowTitle(tr("Unnamed:%1").arg(m_number));
        } else {
            setWindowTitle(QString::fromStdString(s));
        }
    }
}



#include "moc_GraphCanvas.cpp"
