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
        GraphicsCanvas(new GraphView(new GraphScene), parent), 
        m_number(gCanvasNum++)
    {
        m_view      = (GraphView*) GraphicsCanvas::view();
        m_scene     = (GraphScene*) GraphicsCanvas::scene();
        m_scene -> setParent(this);
        m_scene -> setSceneRect(QRectF(0,0,2048,2048));
    }
    
    GraphCanvas::~GraphCanvas()
    {
    }

    void        GraphCanvas::clear()
    {
        m_scene -> clear();
        m_url   = {};
    }

    GDocumentPtr           GraphCanvas::get() const
    {
        return {};
        //return m_scene -> get();
    }
    
    void                    GraphCanvas::set(const GDocument& doc)
    {
        //m_scene -> set(doc);
        //m_url       = doc.url();
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
        if(!is_similar(m_url.scheme, "file"))
            return {};
        if(!m_url.fragment.empty())
            return {};
        if(!m_url.query.empty())
            return {};
        return m_url.path;
    }

    QString GraphCanvas::filename() const
    {
        return QString::fromStdString(filepath().string());
    }

    void    GraphCanvas::updateTitle()
    {
        std::string s = to_string(m_url);
        if(s.empty()){
            setWindowTitle(tr("Unnamed:%1").arg(m_number));
        } else {
            setWindowTitle(QString::fromStdString(s));
        }
    }
}



#include "moc_GraphCanvas.cpp"
