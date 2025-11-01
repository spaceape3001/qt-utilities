////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsScene.hpp"
#include "GraphicsSceneMetaWriter.hpp"
#include <yq/gluon/graphics/GraphicsLayer.hpp>

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/shape/AxBox2.hxx>

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsScene)

namespace yq::gluon {

    GraphicsSceneMeta::GraphicsSceneMeta(std::string_view zName, ObjectQMeta& base, const std::source_location& sl) :
        ObjectQMeta(zName, base, sl)
    {
    }
    
    GraphicsSceneMeta::~GraphicsSceneMeta()
    {
    }
    
    ///////////////////////////////////////////////////////////////////////////
    
    thread_local bool    GraphicsScene::s_printing = false;

    void GraphicsScene::init_meta()
    {
        auto w = writer<GraphicsScene>();
        w.description("Graphics Scene");
    }

    bool GraphicsScene::isPrinting()
    {
        return s_printing;
    }

    ///////////////////////////////////////////////////////////////////////////

    GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
    {
    }
    
    GraphicsScene::GraphicsScene(const QRectF &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
    {
    }

    GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) : 
        QGraphicsScene(x,y,width,height,parent)
    {
    }
    
    GraphicsScene::~GraphicsScene()
    {
    }


    Flags<GraphicsScene::AutoDraw> GraphicsScene::autoDraw() const
    {   
        return m_autoDraw;
    }

    bool    GraphicsScene::autoDraw(AutoDraw ad) const
    {
        return m_autoDraw(ad);
    }

    void    GraphicsScene::autoDrawDisable(AutoDraw ad)
    {
        m_autoDraw.clear(ad);
        invalidate();
    }
    
    void    GraphicsScene::autoDrawEnable(AutoDraw ad)
    {
        m_autoDraw.set(ad);
        invalidate();
    }

    void    GraphicsScene::draw(QPainter* painter, const QRectF& rect)
    {
        if(!painter)
            return ;
        QRectF  area    = rect.isNull() ? sceneRect() : rect;
        drawBackground(painter, area);
        drawItems(painter, area);
        drawForeground(painter, area);
    }

    void    GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect) 
    {
        if(!s_printing)
            QGraphicsScene::drawBackground(painter, rect);
        if(m_autoDraw(AutoDraw_SceneRect))
            drawSceneRect(painter, rect);
        for(QObject* obj : children()){
            if(GraphicsLayer* gl = qobject_cast<GraphicsLayer*>(obj)){
                if(gl -> visibility() == GraphicsVisibility::Background)
                    gl -> draw(painter, rect);
            }
        }
    }

    void    GraphicsScene::drawItems(QPainter *painter, const QRectF &rect) 
    {
        QStyleOptionGraphicsItem    options;
        options.exposedRect         = rect;
        
        for(QObject* obj : children()){
            if(GraphicsLayer* gl = qobject_cast<GraphicsLayer*>(obj)){
                if(gl -> visibility() == GraphicsVisibility::Items)
                    gl -> draw(painter, rect);
            }
        }
        for(QGraphicsItem* it : items()){
            it->paint(painter, &options, nullptr);
        }
    }

    void    GraphicsScene::drawForeground(QPainter *painter, const QRectF &rect) 
    {
        if(!s_printing)
            QGraphicsScene::drawForeground(painter, rect);
        for(QObject* obj : children()){
            if(GraphicsLayer* gl = qobject_cast<GraphicsLayer*>(obj)){
                if(gl -> visibility() == GraphicsVisibility::Foreground)
                    gl -> draw(painter, rect);
            }
        }
    }
        
        
    void    GraphicsScene::drawSceneRect(QPainter *painter, const QRectF &rect)
    {
        if(!painter)
            return;
            
        painter->save();
        QRectF      qsr  = sceneRect();
        AxBox2D     sr(qsr);
        AxBox2D     fill(rect);
        
        if(rect.isNull() || fill.eclipses(sr)){
            painter->setPen(m_sceneRectPen);
            if(!s_printing)
                painter->setBrush(m_sceneRectBrush);
            painter->drawRect(qsr);
        } else if(sr.eclipses(fill)){
            if(!s_printing)
                painter->fillRect(qsr, m_sceneRectBrush);
        } else {
            painter->setPen(m_sceneRectPen);
            if(!s_printing)
                painter->fillRect(rect.intersected(qsr), m_sceneRectBrush);
            
            //  And now, the edges
            auto in = sr & fill;
            if(fill.lo.y <= sr.lo.y)    //  top edge
                painter->drawLine(in.lo.x, in.lo.y, in.hi.x, in.lo.y);
            if(fill.hi.y >= sr.hi.y)    //  bottom edge
                painter->drawLine(in.lo.x, in.hi.y, in.hi.x, in.hi.y);
            if(fill.lo.x <= sr.lo.x)    //  left edge
                painter->drawLine(in.lo.x, in.lo.y, in.lo.x, in.hi.y);
            if(fill.hi.x >= sr.hi.x)    //  right edge
                painter->drawLine(in.hi.x, in.lo.y, in.hi.x, in.hi.y);
        }
        painter->restore();
    }

    void    GraphicsScene::print(QPainter* painter, const QRectF& rect)
    {
        bool    old = s_printing;
        s_printing = true;
        draw(painter, rect);
        s_printing = old;
    }
     
    QBrush  GraphicsScene::sceneRectBrush() const
    {
        return m_sceneRectBrush;
    }

    QPen    GraphicsScene::sceneRectPen() const
    {
        return m_sceneRectPen;
    }
    
    void    GraphicsScene::setSceneRectBrush(QBrush v)
    {
        m_sceneRectBrush = v;
    }

    void    GraphicsScene::setSceneRectPen(QPen v)
    {
        m_sceneRectPen  = v;
    }
}

#include "moc_GraphicsScene.cpp"
