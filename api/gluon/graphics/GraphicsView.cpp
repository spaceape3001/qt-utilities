////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsView.hpp"
#include "GraphicsViewInfoWriter.hpp"

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

#include <gluon/logging.hpp>
#include <gluon/graphics/GraphicsScene.hpp>
#include <gluon/graphics/GraphicsTool.hpp>

#include <yq/shape/AxBox2.hpp>
#include <yq/shape/Size2.hpp>
#include <yq/shape/AxBox2.hxx>

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsView)

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
    GraphicsViewInfo::GraphicsViewInfo(std::string_view zName, WidgetQInfo& base, const std::source_location& sl) :
        WidgetQInfo(zName, base, sl)
    {
    }
    
    GraphicsViewInfo::~GraphicsViewInfo()
    {
    }

    ///////////////////////////////////////////////////////////////////////////

    void GraphicsView::init_info()
    {
        auto w = writer<GraphicsView>();
        w.description("Graphics View");
    }

    GraphicsView::GraphicsView(GraphicsScene*scene, QWidget*parent) : QGraphicsView(scene, parent), m_scene(scene)
    {
        assert(scene);
        setMouseTracking(true);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
    
    GraphicsView::~GraphicsView()
    {
    }

    Flags<GraphicsView::AutoDraw> GraphicsView::autoDraw() const
    {   
        return m_autoDraw;
    }

    bool    GraphicsView::autoDraw(AutoDraw ad) const
    {
        return m_autoDraw(ad);
    }

    void    GraphicsView::autoDrawDisable(AutoDraw ad)
    {
        m_autoDraw.clear(ad);
    }
    
    void    GraphicsView::autoDrawEnable(AutoDraw ad)
    {
        m_autoDraw.set(ad);
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
    
    void    GraphicsView::drawBackground(QPainter *painter, const QRectF &rect) 
    {
        QGraphicsView::drawBackground(painter, rect);
        if(m_autoDraw(AutoDraw_SceneRect))
            drawSceneRect(painter, rect);
    }
    
    void            GraphicsView::drawSceneRect(QPainter *painter, const QRectF &rect)
    {
        if(!painter)
            return;
        painter->save();
        QRectF      qsr  = m_scene->sceneRect();
        AxBox2D     sr(qsr);
        AxBox2D     fill(rect);
        
        if(rect.isNull() || fill.eclipses(sr)){
            painter->setPen(m_sceneRectPen);
            painter->setBrush(m_sceneRectBrush);
            painter->drawRect(qsr);
        } else if(sr.eclipses(fill)){
            painter->fillRect(qsr, m_sceneRectBrush);
        } else {
            painter->setPen(m_sceneRectPen);
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

    QBrush  GraphicsView::sceneRectBrush() const
    {
        return m_sceneRectBrush;
    }

    QPen    GraphicsView::sceneRectPen() const
    {
        return m_sceneRectPen;
    }
    
    void    GraphicsView::setSceneRectBrush(QBrush v)
    {
        m_sceneRectBrush = v;
    }

    void    GraphicsView::setSceneRectPen(QPen v)
    {
        m_sceneRectPen  = v;
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
