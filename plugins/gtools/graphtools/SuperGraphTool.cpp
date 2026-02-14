////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "SuperGraphTool.hpp"

#include <yq/gluon/core/urect.hpp>
#include <yq/gluon/interface/PositionInterface.hpp>
#include <yq/graphQt/GraphCanvas.hpp>
#include <yq/graphQt/GraphItem.hpp>
#include <yq/graphQt/GraphEdgeItem.hpp>
#include <yq/graphQt/GraphLineItem.hpp>
#include <yq/graphQt/GraphNodeItem.hpp>
#include <yq/graphQt/GraphPointCapture.hpp>
#include <yq/graphQt/GraphPortItem.hpp>
#include <yq/graphQt/GraphScene.hpp>
#include <yq/graphQt/GraphShapeItem.hpp>
#include <yq/graphQt/GraphTextItem.hpp>
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
    
    May need to add in "Control points" to the graph, 
    basically waypoints?
*/


namespace yq::gluon {
    static const GraphView::CaptureOptions  kGeneral{ .items=true, .nodes=true, .ports=true };
    static const double                     kDragThreshhold = 3;
    
    static QRectF   qBoundingRect(const QGraphicsItem& item)
    {
        return item.mapToScene(item.boundingRect()).boundingRect();
    }


    SuperGraphTool::SuperGraphTool(QObject* parent) : GraphicsTool(parent)
    {
        m_select.pen.setWidth(2);
        m_select.pen.setStyle(Qt::DashLine);
        
        m_outline.pen.setWidth(1);
        m_outline.pen.setColor(Qt::blue);
        
        m_badPen.setWidth(2);
        m_badPen.setColor(Qt::red);
        
        m_port.bad.setWidth(2);
        m_port.bad.setColor(Qt::red);
        
        m_port.good.setWidth(1);
        m_port.good.setColor(Qt::green);
    }
    
    SuperGraphTool::~SuperGraphTool()
    {
    }
    
    ////////////////////////////////

    void    SuperGraphTool::_cancel()
    {
        m_mode  = Mode::None;
        m_flags = {};
    }

    bool    SuperGraphTool::_check() const 
    { 
        return m_canvas && m_view && m_scene; 
    }

    void    SuperGraphTool::_decruft()
    {
        invalidateToolLayer();
        m_flags -= F::SelectRect;
        m_flags -= F::OutlineRect;
    }

    bool    SuperGraphTool::_dragging(QSinglePointEvent*evt) const
    {
        QPointF del = (evt->position() - m_lastPosition);
        return fabs(del.x())+fabs(del.y()) >= kDragThreshhold;
    }
    
    QPointF SuperGraphTool::_last(QSinglePointEvent*evt)
    {
        m_lastPosition  = evt->position();
        QPointF pt      = m_transform.map(m_lastPosition);
        QPointF ret     = m_flags(F::Last) ? (pt - m_lastPoint) : QPointF(0,0);
        m_lastPoint     = pt;
        m_flags |= F::Last;
        return ret;
    }

    bool    SuperGraphTool::_select(QGraphicsItem*qi)
    {
        if(!qi)
            return false;
        bool ret    = !qi->isSelected();
        m_canvas->selectThis(qi);
        return ret;
    }

    bool    SuperGraphTool::_tselect(QGraphicsItem*qi)
    {
        if(!qi)
            return false;
        if(qi->isSelected()){
            m_canvas -> deselect(qi);
            return false;
        } else {
            m_canvas -> select(qi);
            return true;
        }
    }

    void    SuperGraphTool::_transform()
    {
        m_transform = m_view -> viewportTransform().inverted();
        m_flags |= F::Transform;
    }

    bool    SuperGraphTool::_wheel() const
    {
        return true;
    }
    
    ////////////////////////////////


    void    SuperGraphTool::activating()
    {
        std::tie(m_scene, m_view, m_canvas) = contextAs<GraphScene,GraphView,GraphCanvas>();
    }


    void    SuperGraphTool::deactivating()
    {
        m_view  = nullptr;
    }


    void    SuperGraphTool::drawToolLayer(QPainter* painter, const QRectF&) 
    {
        if(m_flags(F::SelectRect)){
            painter -> save();
            painter -> setPen(m_select.pen);
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
            painter -> setPen(m_port.bad);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawLine(m_pinRect.topLeft(), m_pinRect.bottomRight());
            painter -> drawLine(m_pinRect.bottomLeft(), m_pinRect.topRight());
            painter -> restore();
        }
        
        if(m_flags(F::OutlineRect)){
            painter -> save();
            if(m_outline.use != QPen()){
                painter -> setPen(m_outline.use);
            } else {
                painter -> setPen(m_outline.pen);
            }
            painter -> setBrush(Qt::NoBrush);
            painter -> drawEllipse(m_outlineRect);
            painter -> drawRect(m_outlineRect);
            painter -> restore();
        }
    }

    void 	SuperGraphTool::keyPressEvent(QKeyEvent* evt)
    {
        if(!_check())
            return;

        switch(m_mode){
        default:
            break;
        }
    }
    
    void 	SuperGraphTool::keyReleaseEvent(QKeyEvent* evt)
    {
        if(!_check())
            return;

        switch(m_mode){
        default:
            break;
        }
    }
    
    void    SuperGraphTool::mouseDoubleClickEvent(QMouseEvent* evt)
    {
        if(!_check())
            return;

        switch(m_mode){
        default:
            break;
        }
    }
    
    void    SuperGraphTool::mouseMoveEvent(QMouseEvent* evt)
    {
        if(!_check())
            return;

        switch(m_mode){
        case Mode::None:
            _decruft();
            if(GraphPointCapture cap = m_view->capture(evt, kGeneral); cap.qItem){
                m_outlineRect       = qBoundingRect(*cap.qItem);
                m_flags |= F::OutlineRect;
                if(cap.port){
                    m_outline.use   = m_port.good;
                } else {
                    m_outline.use   = QPen{};
                }
            }
            break;
        case Mode::Move:
            {
                QPointF del = _last(evt);
                for(auto q : m_canvas->selected()){
                    if(PositionInterface* ph = dynamic_cast<PositionInterface*>(q))
                        ph->position(MOVE, del);
                }
            }
            break;
        case Mode::Skip:
            break;
        case Mode::Pan:
            m_view->translateBy(_last(evt));
            break;
        case Mode::PressNothing:
            if(_dragging(evt))
                m_mode          = Mode::Select;
            break;
        case Mode::PressNode:
            if(_dragging(evt)){
                _select(m_capture.node);
                m_mode  = Mode::Move;
            }
            break;
        case Mode::PressPort:
            if(_dragging(evt)){
                // create edge
            }
            break;
        case Mode::PressEdge:
            if(_dragging(evt)){
                //  add point
            }
        case Mode::PressText:
            if(_dragging(evt)){
                _select(m_capture.text->qItem());
                m_mode  = Mode::Move;
            }
            break;
        case Mode::PressLine:
            if(_dragging(evt)){
                //  add waypoint
            }
            break;
        case Mode::PressShape:
            if(_dragging(evt)){
                _select(m_capture.shape->qItem());
                m_mode  = Mode::Move;
            }
            break;
        case Mode::Select:
            _decruft();
            _last(evt);
            m_selectRect    = qRect(m_lastPoint, m_capture.point);
            m_flags        |= F::SelectRect;
            break;
        default:
            break;
        }
    }
    
    void    SuperGraphTool::mousePressEvent(QMouseEvent* evt)
    {
        if(!_check())
            return;
        evt -> accept();

        _decruft();
        
        if(evt->button() == Qt::RightButton){
            _cancel();
            m_canvas -> selectNone();
            m_mode  = Mode::Skip;
            return;
        }
        
        _transform();
        _last(evt);

        m_capture  = m_view -> capture(evt, kGeneral);
        
        if(m_capture.edge){
            switch(evt->modifiers()){
            case Qt::NoModifier:
                if(_select(m_capture.edge->qItem())){
                    m_mode  = Mode::PressEdge;
                } else
                    m_mode  = Mode::Move;
                break;
            case Qt::ControlModifier:
                if(_tselect(m_capture.edge->qItem())){
                    m_mode  = Mode::Move;
                } else
                    m_mode  = Mode::Skip;
                break;
            default:
                break;
            }
        } else if(m_capture.port){
            switch(evt->modifiers()){
            case Qt::NoModifier:
                m_mode  = Mode::PressPort;
                break;
            default:
                break;
            }
        } else if(m_capture.node){
            switch(evt->modifiers()){
            case Qt::NoModifier:
                if(_select(m_capture.node)){
                    m_mode  = Mode::PressNode;
                } else {
                    m_mode  = Mode::Move;
                }
                break;
            case Qt::ControlModifier:
                if(_tselect(m_capture.node)){
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::Skip;
                }
                break;
            default:
                break;
            }
        } else if(m_capture.text){
            switch(evt->modifiers()){
            case Qt::NoModifier:
                if(_select(m_capture.text->qItem())){
                    m_mode  = Mode::PressText;
                } else {
                    m_mode  = Mode::Move;
                }
                break;
            case Qt::ControlModifier:
                if(_tselect(m_capture.text->qItem())){
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::Skip;
                }
                break;
            default:
                break;
            }
        } else if(m_capture.line){
            switch(evt->modifiers()){
            case Qt::NoModifier:
                if(_select(m_capture.line->qItem())){
                    m_mode  = Mode::PressLine;
                } else {
                    m_mode  = Mode::Move;
                }
                break;
            case Qt::ControlModifier:
                if(_tselect(m_capture.line->qItem())){
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::Skip;
                }
                break;
            default:
                break;
            }
        } else if(m_capture.shape){
            switch(evt->modifiers()){
            case Qt::NoModifier:
                if(_select(m_capture.shape->qItem())){
                    m_mode  = Mode::PressShape;
                } else {
                    m_mode  = Mode::Move;
                }
                break;
            case Qt::ControlModifier:
                if(_tselect(m_capture.shape->qItem())){
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::Skip;
                }
                break;
            default:
                break;
            }
        } else {
            switch(evt->modifiers()){
            case Qt::NoModifier:
                m_mode  = Mode::PressNothing;
                break;
            case Qt::ControlModifier:
                m_mode  = Mode::Pan;
                break;
            default:
                break;
            }
        }
    }
    
    void    SuperGraphTool::mouseReleaseEvent(QMouseEvent* evt)
    {
        if(!_check())
            return;

        switch(m_mode){
        case Mode::Select:
            m_canvas -> selectThese(m_scene->items(m_selectRect));
            break;
        default:    
            break;
        }
        
        // will likely refine (later)
        _cancel();
        _decruft();
        evt->accept();
    }


    void    SuperGraphTool::wheelEvent(QWheelEvent* evt)
    {
        if(_wheel()){
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
