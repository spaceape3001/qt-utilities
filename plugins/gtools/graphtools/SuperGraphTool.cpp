////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "SuperGraphTool.hpp"

#include <yq/color/colors.hpp>
#include <yq/gluon/core/ucolor.hpp>
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
        m_selectPen.setWidth(2);
        m_selectPen.setStyle(Qt::DashLine);
        
        m_outlinePen.setWidth(1);
        m_outlinePen.setColor(Qt::blue);
        
        m_badPen.setWidth(2);
        m_badPen.setColor(Qt::red);
        
        m_pinPen.setWidth(1);
        m_pinPen.setColor(qColor(color::ForestGreen));
        
        m_linePen.setWidth(1);
        m_linePen.setColor(Qt::blue);
    }
    
    SuperGraphTool::~SuperGraphTool()
    {
    }
    
    ////////////////////////////////

    void    SuperGraphTool::_cancel()
    {
        m_mode  = Mode::None;
        
        _decruft();
        m_flags = {};
    }

    bool    SuperGraphTool::_check() const 
    { 
        return m_canvas && m_view && m_scene; 
    }

    void    SuperGraphTool::_decruft()
    {
        invalidateToolLayer();
        
        m_linePath  = QPainterPath();
        m_flags    -= F::PinDraw;
        m_flags    -= F::SelectRect;
        m_flags    -= F::OutlineRect;
    }

    bool    SuperGraphTool::_dragging(QSinglePointEvent*evt) const
    {
        QPointF del = (evt->position() - m_capture.position);
        return fabs(del.x())+fabs(del.y()) >= kDragThreshhold;
    }
    
    QPointF SuperGraphTool::_last(QSinglePointEvent*evt)
    {
        QPointF         last    = m_last.point;
        m_last          = m_view->capture(evt, kGeneral);
        if(m_flags(F::Last)){
            return m_last.point - last;
        } else {
            m_flags |= F::Last;
            return QPointF(0.,0.);
        }
    }

    bool    SuperGraphTool::_select(QGraphicsItem*qi)
    {
        if(!qi)
            return false;
        bool ret    = qi->isSelected();
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
        if(m_canvas){
            m_graph     = m_canvas -> get();
        } else if(m_scene){
            m_graph     = m_scene -> get();
        } else
            m_graph     = {};
    }

    void    SuperGraphTool::contextMenuEvent(QContextMenuEvent*evt) 
    {
        if(!_check())
            return;

        evt->accept();
        auto cap    = m_view -> capture(evt->pos(), kGeneral);
        if(cap.port){
            m_canvas -> rightClick(cap.port->data());
        } else if(cap.node){
            m_canvas -> rightClick(cap.node->data());
        } else if(cap.edge){
            m_canvas -> rightClick(cap.edge->data());
        } else if(cap.text){
            m_canvas -> rightClick(cap.text->data());
        } else if(cap.shape){
            m_canvas -> rightClick(cap.shape->data());
        } else if(cap.line){
            m_canvas -> rightClick(cap.line->data());
        } else {
            m_canvas -> rightClick(m_canvas->get());
        }
    }

    void    SuperGraphTool::deactivating()
    {
        m_view  = nullptr;
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
        
        if(m_flags(F::PinDraw) && m_flags(F::PinGood)){
            painter -> save();
            painter -> setPen(m_pinPen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawEllipse(m_pinRect);
            painter -> restore();
        }
        
        if(m_flags(F::PinDraw) && !m_flags(F::PinGood)){
            painter -> save();
            painter -> setPen(m_badPen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawLine(m_pinRect.topLeft(), m_pinRect.bottomRight());
            painter -> drawLine(m_pinRect.bottomLeft(), m_pinRect.topRight());
            painter -> restore();
        }
        
        if(m_flags(F::OutlineRect)){
            painter -> save();
            painter -> setPen(m_outlinePen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawEllipse(m_outlineRect);
            painter -> drawRect(m_outlineRect);
            painter -> restore();
        }
        
        if(!m_linePath.isEmpty()){
            painter -> save();
            painter -> setPen(m_linePen);
            painter -> setBrush(Qt::NoBrush);
            painter -> drawPath(m_linePath);
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
    
    //  context...
    
    void    SuperGraphTool::mouseDoubleClickEvent(QMouseEvent* evt)
    {
        if(!_check())
            return;

        GraphPointCapture cap   = m_view->capture(evt, kGeneral);
        if(cap.port){
            m_canvas -> doubleClick(cap.port->data());
        } else if(cap.node){
            m_canvas  -> doubleClick(cap.node->data());
        } else if(cap.edge){
            m_canvas  -> doubleClick(cap.edge->data());
        } else if(cap.text){
            m_canvas  -> doubleClick(cap.text->data());
        } else if(cap.shape){
            m_canvas  -> doubleClick(cap.shape->data());
        } else if(cap.line){
            m_canvas  -> doubleClick(cap.line->data());
        }
    }
    
    void    SuperGraphTool::mouseMoveEvent(QMouseEvent* evt)
    {
        if(!_check())
            return;

        switch(m_mode){
        case Mode::DragNewEdge:
            _decruft();
            _last(evt);
            m_linePath  = m_scene -> path_for({ m_capture.point, m_last.point });
            if(m_last.port && (m_capture.port != m_last.port)){
                m_flags     |= F::PinDraw;
                m_pinRect       = qBoundingRect(*m_last.qItem);
                
                //  eventually bind to another routine
                bool    gIn         = m_flags(F::WantInput) && m_last.port->data().is_input();
                bool    gOut        = m_flags(F::WantOutput) && m_last.port->data().is_output();
                bool    gConnected  = m_graph.connected(m_capture.port->data(), m_last.port->data());
                
                if((gIn || gOut) && !gConnected){
                    m_flags    |= F::PinGood;
                } else {
                    m_flags    -= F::PinGood;
                }
            }
            invalidateToolLayer();
            break;
        case Mode::None:
            _decruft();
            _last(evt);
           
            if(m_last.qItem){
                if(m_last.port){
                    m_pinRect       = qBoundingRect(*m_last.qItem);
                    m_flags        |= F::PinDraw;
                    if(m_last.port->data().is_output()){
                        m_flags    |= F::PinGood;
                    } else {
                        m_flags    -= F::PinGood;
                    }
                } else {
                    m_outlineRect       = qBoundingRect(*m_last.qItem);
                    m_flags         |= F::OutlineRect;
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
                m_scene -> update();
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
                m_mode  = Mode::DragNewEdge;
                if(m_capture.port->data().is_input())
                    m_flags |= F::WantOutput;
                if(m_capture.port->data().is_output())
                    m_flags |= F::WantInput;
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
            m_selectRect    = qRect(m_last.point, m_capture.point);
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
                m_mode   = Mode::PressPort;
                m_flags -= F::PinGood;
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
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::PressText;
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
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::PressLine;
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
                    m_mode  = Mode::Move;
                } else {
                    m_mode  = Mode::PressShape;
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
        case Mode::DragNewEdge:
            if(m_capture.port && m_last.port && m_flags(F::PinGood))
                m_scene -> add( m_graph.connect(m_capture.port->data(), m_last.port->data()));
            break;
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
