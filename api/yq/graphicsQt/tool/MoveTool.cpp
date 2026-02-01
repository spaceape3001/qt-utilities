////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "MoveTool.hpp"
#include <yq/gluon/core/upoint.hpp>
#include <yq/gluon/interface/PositionInterface.hpp>

#include <yq/graphicsQt/GraphicsCanvas.hpp>
#include <yq/graphicsQt/GraphicsScene.hpp>
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>
#include <yq/graphicsQt/GraphicsView.hpp>

#include <QGraphicsItem>
#include <QMouseEvent>
#include <QWheelEvent>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::MoveTool)

namespace yq::gluon {
    struct MoveTool::D {
        QGraphicsItem*      item    = nullptr;
        PositionInterface*  pIntf   = nullptr;
        QPointF             start;
    };

    MoveTool::MoveTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    MoveTool::~MoveTool()
    {
    }
    
    void    MoveTool::deactivating() 
    {
        m_inDrag    = false;
        m_items.clear();
    }

    void    MoveTool::mouseMoveEvent(QMouseEvent* evt) 
    {
        GraphicsView*   gv  = view();
        if(!gv)
            return ;
        if(!m_inDrag)
            return ;
        if(m_items.empty())
            return ;
        evt -> accept();
        QPointF     del  = gv -> mapToScene(evt -> position()) - m_start;
        for(auto& d : m_items){
            QPointF p2  = d.start + del;
            if(d.pIntf){
                d.pIntf -> position(SET, p2);
            } else {
                d.item -> setPos(p2);
            }
        }
    }
    
    void    MoveTool::mousePressEvent(QMouseEvent* evt)
    {
        evt -> accept();
        
        auto [sc, gv, cvs]  = context();
        if(!(sc&&gv&&cvs))
            return;

        m_start = gv -> mapToScene(evt->position());
            
        if(cvs->selected().empty())
            return;
        
        for(QGraphicsItem* qi : cvs->selected()){
            D       d{.item=qi};
            if(PositionInterface* pi = dynamic_cast<PositionInterface*>(qi)){
                d.pIntf     = pi;
                d.start     = pi -> position();
            } else {
                d.start     = qi -> pos();
            }
        
            m_items.push_back(d);
        }

        m_inDrag    = true;
    }
    
    void    MoveTool::mouseReleaseEvent(QMouseEvent*evt) 
    {
        deactivating();
        evt -> accept();
    }

    void    MoveTool::wheelEvent(QWheelEvent*evt) 
    {
        if(m_inDrag){
            evt -> ignore();
        } else
            GraphicsTool::wheelEvent(evt);
    }

    void MoveTool::init_meta()
    {
        auto w = writer<MoveTool>();
        w.description("Move Tool");
        w.icon(0, "yq/icon/tool/move.svg");
    }
}

#include "moc_MoveTool.cpp"
