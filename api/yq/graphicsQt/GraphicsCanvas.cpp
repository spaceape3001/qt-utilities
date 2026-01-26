////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsCanvas.hpp"
#include "GraphicsScene.hpp"
#include "GraphicsTool.hpp"
#include "GraphicsView.hpp"
#include <QVBoxLayout>

namespace yq::gluon {
    GraphicsCanvas::GraphicsCanvas(QWidget*parent) : GraphicsCanvas(new GraphicsScene, parent)
    {
        m_scene -> setParent(this);
    }
    
    GraphicsCanvas::GraphicsCanvas(GraphicsScene* sc, QWidget*parent) : GraphicsCanvas(new GraphicsView(sc), parent)
    {
    }
    
    GraphicsCanvas::GraphicsCanvas(GraphicsView* sv, QWidget*parent) : SubWindow(parent), m_scene(sv->scene()), m_view(sv)
    {
        m_view -> featureEnable(gluon::GraphicsView::Feature_MouseWheelZoom);
        m_view -> featureEnable(gluon::GraphicsView::Feature_MouseWheelRotate);
        m_view -> setMouseWheelRotateModifiers(Qt::AltModifier);

        QVBoxLayout*    layout  = new QVBoxLayout;
        layout -> addWidget(m_view);
        layout -> setContentsMargins(0,0,0,0);
        setLayout(layout);

        setWindowTitle(tr("Some Canvas"));
    }
    
    GraphicsCanvas::~GraphicsCanvas()
    {
        m_tools.clear();
    }

    uint64_t    GraphicsCanvas::currentTool() const
    {
        GraphicsTool*   gt  = m_view->tool();
        if(!gt)
            return 0;
        return gt->metaInfo().id();
    }

    void    GraphicsCanvas::setBackgroundBrush(QBrush v)
    {
        m_scene -> setBackgroundBrush(v);
    }

    void    GraphicsCanvas::setEdgePen(QPen v)
    {
        m_scene -> autoDrawEnable(gluon::GraphicsScene::AutoDraw_SceneRect);
        m_scene -> setSceneRectPen(v);
    }
    
    void    GraphicsCanvas::setPaperBrush(QBrush v)
    {
        m_scene -> autoDrawEnable(gluon::GraphicsScene::AutoDraw_SceneRect);
        m_scene -> setSceneRectBrush(v);
    }

    void    GraphicsCanvas::setTool(uint64_t qu)
    {
        GraphicsTool*   gt  = nullptr;
        if(auto itr = m_tools.find(qu); itr != m_tools.end()){
            gt  = itr->second;
        } else {
            if(const GraphicsToolMeta* gtm = dynamic_cast<const GraphicsToolMeta*>(Meta::lookup((meta_id_t) qu))){
                if(ObjectQ* obj  = gtm -> create(this)){
                    if(gt = dynamic_cast<GraphicsTool*>(obj); !gt){
                        delete obj;
                    }
                }
            }
            m_tools[qu] = gt;
        }
        
        if(gt && (gt != m_view->tool())){
            m_view -> setTool(gt);
            emit toolChanged((quint64) gt->metaInfo().id());
        }
    }
    
}

#include "moc_GraphicsCanvas.cpp"
