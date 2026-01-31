////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphCanvas.hpp"
#include "GraphScene.hpp"
#include "GraphView.hpp"

#include <yq/text/match.hpp>
#include <yq/graph/GDocument.hpp>
#include <QHBoxLayout>
#include <QVBoxLayout>


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
