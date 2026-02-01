////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "GraphicsView.hpp"
#include "GraphicsScene.hpp"
#include "GraphicsTool.hpp"

#include <QContextMenuEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFocusEvent>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QResizeEvent>
#include <QScreen>
#include <QWheelEvent>


namespace {
    int     firstNonZero(const QPoint&p)
    {
        int x = p.x();
        if(x)
            return x;
        return p.y();
    }
}


namespace yq::gluon {
    GraphicsView::GraphicsView(GraphicsScene*scene, QWidget*parent) : 
        QGraphicsView(scene, parent), m_scene(scene)
    {
        assert(scene);
        setMouseTracking(true);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setTransformationAnchor(NoAnchor);
    }
    
    GraphicsView::~GraphicsView()
    {
    }


    void 	GraphicsView::contextMenuEvent(QContextMenuEvent*evt) 
    {
        if(m_tool){
            m_tool -> contextMenuEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::contextMenuEvent(evt);
    }
        
    void 	GraphicsView::dragEnterEvent(QDragEnterEvent*evt) 
    {
        if(m_tool){
            m_tool -> dragEnterEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::dragEnterEvent(evt);
    }
    
    void 	GraphicsView::dragLeaveEvent(QDragLeaveEvent*evt) 
    {
        if(m_tool){
            m_tool -> dragLeaveEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::dragLeaveEvent(evt);
    }
    
    void 	GraphicsView::dragMoveEvent(QDragMoveEvent*evt) 
    {
        if(m_tool){
            m_tool -> dragMoveEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::dragMoveEvent(evt);
    }

    void 	GraphicsView::drawBackground(QPainter *painter, const QRectF &rect) 
    {
        QGraphicsView::drawBackground(painter, rect);
    }
    
    void 	GraphicsView::drawForeground(QPainter *painter, const QRectF &rect) 
    {
        QGraphicsView::drawForeground(painter, rect);
        if(m_tool)
            m_tool -> drawToolLayer(painter, rect);
    }
    
    void 	GraphicsView::dropEvent(QDropEvent*evt) 
    {
        if(m_tool){
            m_tool -> dropEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::dropEvent(evt);
    }

    void 	GraphicsView::enterEvent(QEnterEvent* evt) 
    {
        if(m_tool){
            m_tool -> enterEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::enterEvent(evt);
    }

    bool            GraphicsView::feature(Feature v) const
    {
        return m_features;
    }
    
    void            GraphicsView::featureDisable(Feature v)
    {
        m_features.clear(v);
    }
    
    void            GraphicsView::featureEnable(Feature v)
    {
        m_features.set(v);
    }

    bool            GraphicsView::featureMouseWheelRotate() const
    {
        return m_features[Feature::MouseWheelRotate];
    }
    
    bool            GraphicsView::featureMouseWheelZoom() const
    {
        return m_features[Feature::MouseWheelZoom];
    }

    Flags<GraphicsView::Feature> GraphicsView::features() const
    {
        return m_features;
    }

    void    GraphicsView::fitToScene()
    {
        QGraphicsScene* sc  = scene();
        if(sc){
            fitInView(sc->sceneRect(), Qt::KeepAspectRatio);
            zoomChanged(zoomFactor());
        }
    }

    void 	GraphicsView::focusInEvent(QFocusEvent*evt) 
    {
        if(m_tool){
            m_tool -> focusInEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::focusInEvent(evt);
    }
    
    void 	GraphicsView::focusOutEvent(QFocusEvent*evt) 
    {
        if(m_tool){
            m_tool -> focusOutEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::focusOutEvent(evt);
    }

    void    GraphicsView::invalidateForeground()
    {
        m_scene->invalidate(QRectF(), QGraphicsScene::ForegroundLayer);
    }
    
    bool    GraphicsView::isWheelRotate(QWheelEvent*evt) const
    {
        return featureMouseWheelRotate() && (evt->modifiers() == m_mouseWheelRotateModifiers);
    }
    
    bool    GraphicsView::isWheelZoom(QWheelEvent*evt) const
    {
        return featureMouseWheelZoom() && (evt->modifiers() == m_mouseWheelZoomModifiers);
    }

    void 	GraphicsView::keyPressEvent(QKeyEvent*evt) 
    {
        if(m_tool){
            m_tool -> keyPressEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::keyPressEvent(evt);
    }
    
    void 	GraphicsView::keyReleaseEvent(QKeyEvent*evt)
    {
        if(m_tool){
            m_tool -> keyReleaseEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::keyReleaseEvent(evt);
    }

    void 	GraphicsView::leaveEvent(QEvent* evt) 
    {
        if(m_tool){
            m_tool -> leaveEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::leaveEvent(evt);
    }

    QPointF GraphicsView::mapToScene(const QPointF&pt) const
    {
        return QGraphicsView::mapToScene(pt.toPoint());
    }

    void    GraphicsView::mouseDoubleClickEvent(QMouseEvent* evt)
    {
        if(m_tool){
            m_tool -> mouseDoubleClickEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::mouseDoubleClickEvent(evt);
    }

    void    GraphicsView::mouseMoveEvent(QMouseEvent*evt)
    {
        QPointF     pt  = mapToScene(evt->pos());
        emit mouseAt(pt.x(), pt.y());
        
        if(m_tool){
            m_tool -> mouseMoveEvent(evt);
            if(evt->isAccepted())
                return ;
        }

        QGraphicsView::mouseMoveEvent(evt);
    }
    
    void    GraphicsView::mousePressEvent(QMouseEvent*evt) 
    {
        if(m_tool){
            m_tool -> mousePressEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::mousePressEvent(evt);
    }
    
    void    GraphicsView::mouseReleaseEvent(QMouseEvent*evt)
    {
        if(m_tool){
            m_tool -> mouseReleaseEvent(evt);
            if(evt->isAccepted())
                return;
        }
        QGraphicsView::mouseReleaseEvent(evt);
    }

    void    GraphicsView::resizeEvent(QResizeEvent*evt) 
    {
        QGraphicsView::resizeEvent(evt);
        //gluonInfo << "QGraphicsView::resizeEvent(" << evt->size() << ")";
        resized();
    }

    void    GraphicsView::setMouseWheelRotateModifiers(Qt::KeyboardModifiers v)
    {
        m_mouseWheelRotateModifiers = v;
    }

    void    GraphicsView::setMouseWheelZoomModifiers(Qt::KeyboardModifiers v)
    {
        m_mouseWheelZoomModifiers   = v;
    }
    
    void    GraphicsView::setTool(GraphicsTool* tool)
    {
        if(tool == m_tool)
            return;

        //  cursor may change....
        //  state may reset

        if(m_tool){
            m_tool -> deactivating();
            m_tool -> m_view = nullptr;
        }
        m_tool  = tool;
        if(m_tool){
            m_tool -> m_view    = this;
            m_tool -> activating();
        }
    }

    void    GraphicsView::setZoomFactor(double z)
    {
        z           = fabs(z);
        double  old = zoomFactor();
        scale(z/old, z/old);
        emit zoomChanged(zoomFactor());
    }
    
    QSize   GraphicsView::sizeHint() const
    {
        if(m_features(Feature_MaxViewport)){
            return QGuiApplication::primaryScreen()->virtualSize();
        } else {
            return QGraphicsView::sizeHint();
        }
    }

    void 	GraphicsView::tabletEvent(QTabletEvent*evt)
    {
        if(m_tool){
            m_tool -> tabletEvent(evt);
            if(evt->isAccepted())
                return;
        }
        return QGraphicsView::tabletEvent(evt);
    }

    void            GraphicsView::thWheelRotate(QWheelEvent* evt)
    {
        if(!evt)    
            return ;

        double degrees  = kROTATE * (firstNonZero(evt->angleDelta()) / 120.0);
        rotate(degrees);
        evt -> accept();
    }
    
    void            GraphicsView::thWheelZoom(QWheelEvent*evt)
    {
        if(!evt)
            return ;

        double  factor  = pow(2.0, firstNonZero(evt->angleDelta()) / (120.0 * kDOUBLE));
        scale(factor, factor);
        emit zoomChanged(zoomFactor());
        evt->accept();
    }

    GraphicsTool*   GraphicsView::tool() const
    {
        return const_cast<GraphicsTool*>(m_tool);
    }

    void    GraphicsView::translateBy(const QPointF&amt)
    {
    gluonInfo << "GraphicsView::translateBy(" << amt << ")";
        translate(amt.x(), amt.y());
    }

    bool    GraphicsView::viewportEvent(QEvent*evt) 
    {
        bool ret = QGraphicsView::viewportEvent(evt);
        if(evt->type() == QEvent::Resize)
            viewportResized();
        return ret;
    }

    void    GraphicsView::wheelEvent(QWheelEvent *evt)
    {
        if(m_tool){
            m_tool -> wheelEvent(evt);
            if(evt->isAccepted())
                return;
        }

        if(feature(Feature_MouseWheelZoom) && (evt->modifiers()  == m_mouseWheelZoomModifiers)){
            thWheelZoom(evt);
            return;
        } 
        
        if(feature(Feature_MouseWheelRotate) && (evt->modifiers()  == m_mouseWheelRotateModifiers)){
            thWheelRotate(evt);
            return;
        }
        
        QGraphicsView::wheelEvent(evt);
    }

    void    GraphicsView::zoomBy(double amt)
    {
        scale(amt, amt);
        emit zoomChanged(zoomFactor());
    }

    double  GraphicsView::zoomFactor() const
    {
        QTransform  t   = transform();
        return sqrt(fabs(t.m11()*t.m22()-t.m12()*t.m21()));
    }
    
    void    GraphicsView::zoomIn()
    {
        static double   kFactorIn    = pow(2.0, 1.0/kDOUBLE);
        scale(kFactorIn, kFactorIn);
        emit zoomChanged(zoomFactor());
    }
    
    void    GraphicsView::zoomOut()
    {
        static double   kFactorOut    = pow(2.0, 1.0/kDOUBLE);
        scale(kFactorOut, kFactorOut);
        emit zoomChanged(zoomFactor());
    }
}

#include "moc_GraphicsView.cpp"
