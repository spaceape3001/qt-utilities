////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsCanvas.hpp"
#include "GraphicsScene.hpp"
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
    
    void    GraphicsCanvas::setBackgroundBrush(QBrush v)
    {
        m_scene -> setBackgroundBrush(v);
    }
}

#include "moc_GraphicsCanvas.cpp"
