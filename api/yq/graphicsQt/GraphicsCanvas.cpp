////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "GraphicsCanvas.hpp"
#include "GraphicsScene.hpp"
#include "GraphicsTool.hpp"
#include "GraphicsView.hpp"
#include <yq/gluon/interface/SelectedInterface.hpp>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QGraphicsColorizeEffect>

namespace yq::gluon {
    GraphicsCanvas::GraphicsCanvas(QWidget*parent) : GraphicsCanvas(new GraphicsScene, parent)
    {
        m_scene -> setParent(this);
    }
    
    GraphicsCanvas::GraphicsCanvas(GraphicsScene* sc, QWidget*parent) : GraphicsCanvas(new GraphicsView(sc), parent)
    {
    }
    
    GraphicsCanvas::GraphicsCanvas(GraphicsView* sv, QWidget*parent) : UndoSubWindow(parent), m_scene(sv->scene()), m_view(sv)
    {
        m_view -> featureEnable(gluon::GraphicsView::Feature_MouseWheelZoom);
        m_view -> featureEnable(gluon::GraphicsView::Feature_MouseWheelRotate);
        m_view -> setMouseWheelRotateModifiers(Qt::AltModifier);
        m_view -> setMouseWheelZoomModifiers(Qt::ControlModifier);

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

    bool    GraphicsCanvas::feature(Feature f) const
    {
        return m_features(f);
    }
    
    void    GraphicsCanvas::featureEnable(Feature f)
    {
        m_features.set(f);
        m_scene->invalidate();
    }
    
    void    GraphicsCanvas::featureDisable(Feature f)
    {
        m_features.clear(f);
        m_scene->invalidate();
    }

    void    GraphicsCanvas::focusMe()
    {
        m_view -> setFocus();
    }

    bool    GraphicsCanvas::hasSelectEffect() const
    {
        return feature(Feature::SelectEffect);
    }

    void    GraphicsCanvas::select(QGraphicsItem*qi)
    {
        if(!qi)
            return ;
        qi -> setSelected(true);
        if(SelectedInterface* si = dynamic_cast<SelectedInterface*>(qi))
            si -> selected(SET, true);
        if(hasSelectEffect()){
            if(QGraphicsEffect* qe = selectEffect(qi))
                qi -> setGraphicsEffect(qe);
        }
        std::erase(m_selected, qi);
        m_selected.push_back(qi);
    }

    void    GraphicsCanvas::deselect(QGraphicsItem*qi)
    {
        if(!qi)
            return ;
        qi -> setSelected(false);
        if(SelectedInterface* si = dynamic_cast<SelectedInterface*>(qi))
            si -> selected(SET, false);
        if(hasSelectEffect())
            qi -> setGraphicsEffect(nullptr);
        std::erase(m_selected, qi);
    }

    void    GraphicsCanvas::selectAll()
    {
        auto qItems  = m_scene -> items();
        for(QGraphicsItem* gi : qItems){
            if(!gi)
                continue;
            select(gi);
        }
    }

    QGraphicsEffect*    GraphicsCanvas::selectEffect(QGraphicsItem*)
    {
        QGraphicsColorizeEffect *ret    = new QGraphicsColorizeEffect;
        ret -> setColor(QColor(0,128,255));
        ret -> setStrength(0.5);
        return ret;
    }

    void    GraphicsCanvas::selectNone()
    {
        m_selected.clear();
        auto qItems  = m_scene -> items();
        for(QGraphicsItem* gi : qItems){
            if(!gi)
                continue;
            deselect(gi);
        }
    }

    void    GraphicsCanvas::selectThis(QGraphicsItem* qi)
    {
        selectNone();
        select(qi);
    }
    
    void    GraphicsCanvas::selectThese(const std::vector<QGraphicsItem*>& itemList)
    {
        selectNone();
        for(QGraphicsItem* it : itemList)
            select(it);
    }

    void    GraphicsCanvas::selectThese(const QList<QGraphicsItem*>& itemList)
    {
        selectNone();
        for(QGraphicsItem* it : itemList)
            select(it);
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
                    gt = dynamic_cast<GraphicsTool*>(obj);
                    if(gt){
                        gt -> m_canvas  = this;
                    } else {
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
