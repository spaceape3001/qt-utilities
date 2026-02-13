////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "SuperGraphTool.hpp"
#include <yq/graphQt/GraphCanvas.hpp>
#include <yq/graphQt/GraphItem.hpp>
#include <yq/graphQt/GraphNodeItem.hpp>
#include <yq/graphQt/GraphPointCapture.hpp>
#include <yq/graphQt/GraphPortItem.hpp>
#include <yq/graphQt/GraphScene.hpp>
#include <yq/graphQt/GraphView.hpp>
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>
#include <QKeyEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

#include <yq/graphicsQt/GraphicsTool.hxx>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::SuperGraphTool)

/*
    Tool Behavior
    
    Click (with control key) -- Drags the canvas around
    
    Click (ie press/release w/o movement nor modifiers)
    
        

*/


namespace yq::gluon {
    static const GraphView::CaptureOptions  kGeneral{ .items=true, .nodes=true, .ports=true };
    static QRectF   qBoundingRect(const QGraphicsItem& item)
    {
        return item.mapToScene(item.boundingRect()).boundingRect();
    }


    SuperGraphTool::SuperGraphTool(QObject* parent) : GraphicsTool(parent)
    {
        m_selectPen.setWidth(2);
        m_selectPen.setStyle(Qt::DashLine);
        
        m_outline.pen.setWidth(1);
        m_outline.pen.setColor(Qt::blue);
        
        m_badPen.setWidth(2);
        m_badPen.setColor(Qt::blue);
    }
    
    SuperGraphTool::~SuperGraphTool()
    {
    }

    void    SuperGraphTool::cancel()
    {
        m_mode  = Mode::None;
    }

    bool    SuperGraphTool::canWheel() const
    {
        return true;
    }
    
    void    SuperGraphTool::deactivating()
    {
    }

    void    SuperGraphTool::decruft()
    {
        invalidateToolLayer();
        m_outline.draw  = false;
    }

    void    SuperGraphTool::drawToolLayer(QPainter* painter, const QRectF&) 
    {
        if(m_flags(F::SelectRect)){
            painter -> save();
            painter -> setPen(m_selectPen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawRect(m_selectRect);
            painter -> restore();
        }
        
        if(m_flags(F::PinGood)){
            painter -> save();
            painter -> setPen(m_outline.pen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawEllipse(m_pinRect);
            painter -> restore();
        }
        
        if(m_flags(F::PinBad)){
            painter -> save();
            painter -> setPen(m_badPen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawLine(m_pinRect.topLeft(), m_pinRect.bottomRight());
            painter -> drawLine(m_pinRect.bottomLeft(), m_pinRect.topRight());
            painter -> restore();
        }
        
        if(m_outline.draw){
            painter -> save();
            painter -> setPen(m_outline.pen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawEllipse(m_outline.rect);
            painter -> drawRect(m_outline.rect);
            painter -> restore();
        }
    }
    
    void 	SuperGraphTool::keyPressEvent(QKeyEvent* evt)
    {
        GraphView*  gv  = dynamic_cast<GraphView*>(view());
        if(!gv)
            return;
            
        switch(m_mode){
        default:
            break;
        }
    }
    
    void 	SuperGraphTool::keyReleaseEvent(QKeyEvent* evt)
    {
        GraphView*  gv  = dynamic_cast<GraphView*>(view());
        if(!gv)
            return;

        switch(m_mode){
        default:
            break;
        }
    }
    
    void    SuperGraphTool::mouseDoubleClickEvent(QMouseEvent* evt)
    {
        GraphView*  gv  = dynamic_cast<GraphView*>(view());
        if(!gv)
            return;

        switch(m_mode){
        default:
            break;
        }
    }
    
    void    SuperGraphTool::mouseMoveEvent(QMouseEvent* evt)
    {
        GraphView*  gv  = dynamic_cast<GraphView*>(view());
        if(!gv)
            return;

        //m_current   = gv->capture(evt, kGeneral);
        switch(m_mode){
        case Mode::None:
            moveNone(evt);
            break;
        case Mode::Pan:
            panMove(evt);
            break;
        default:
            break;
        }
        
        //m_last      = m_current;
    }
    
    void    SuperGraphTool::mousePressEvent(QMouseEvent* evt)
    {
        GraphView*  gv  = dynamic_cast<GraphView*>(view());
        if(!gv)
            return;

        //m_current = m_start = gv -> capture(evt, kGeneral);
        switch(m_mode){
        case Mode::None:
            startPress(evt);
            break;
        default:
            break;
        }
        
        //m_last              = m_current;
    }
    
    void    SuperGraphTool::mouseReleaseEvent(QMouseEvent* evt)
    {
        GraphView*  gv  = dynamic_cast<GraphView*>(view());
        if(!gv)
            return;
            
        //m_current       = gv->capture(evt, kGeneral);
        
        switch(m_mode){
        default:    
            break;
        }
        
        // will likely refine (later)
        cancel();
        decruft();
        
        //m_last          = m_current;
    }
    
    
    void    SuperGraphTool::moveNone(QMouseEvent*evt)
    {
        decruft();
        
        GraphView*  gv      = static_cast<GraphView*>(view());
        GraphPointCapture       cap = gv -> capture(evt, kGeneral);
        
        if(cap.qItem){
            m_outline.rect  = qBoundingRect(*cap.qItem);
            m_outline.draw  = true;
        }

        #if 0
        {
            auto log = gluonInfo;
            log << "SuperGraphTool::moveNone(" << evt->position() << ")\n";
            //log << "  gid> " << cap.gid << "\n";
            if(m_outline.draw)
                log << "  outline> " << m_outline.rect << "\n";
            if(cap.node)
                log << "  node> " << cap.node->data().type() << "\n";
            if(cap.port)
                log << "  port> in=" << cap.port->data().is_input() << ", out=" << cap.port->data().is_output() << '\n';
        }
        #endif
        
        
        evt -> accept();
    }

    void    SuperGraphTool::panMove(QMouseEvent*evt)
    {
        GraphView*  gv      = static_cast<GraphView*>(view());
        QPointF     p2      = m_pan.transform.map(evt->position());
        QPointF     del     = p2 - m_pan.last;
        m_pan.last          = p2;
        gv->translate(del.x(), del.y());
        evt -> accept();
    }

    void    SuperGraphTool::startPress(QMouseEvent*evt)
    {
        switch(evt->modifiers()){
        case Qt::NoModifier:
            m_mode  = Mode::Press;
            break;
        case Qt::ControlModifier:
            m_mode  = Mode::Pan;
            m_pan.transform = static_cast<GraphView*>(view()) -> transform().inverted();
            m_pan.last      = m_pan.transform.map(evt->position());
            break;
        default:
            cancel();
            break;
        }
        evt -> accept();
    }

    void    SuperGraphTool::wheelEvent(QWheelEvent* evt)
    {
        if(canWheel()){
            GraphicsTool::wheelEvent(evt);
        } else {
            evt -> ignore();
        }
    }

    void SuperGraphTool::init_meta()
    {
        auto w = writer<SuperGraphTool>();
        w.description("Super Graph Tool");
        w.icon(0, "yq/icon/tool/super.svg");
    }
}

#include "moc_SuperGraphTool.cpp"
