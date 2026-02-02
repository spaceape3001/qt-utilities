////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "SelectTool.hpp"
#include <yq/graphicsQt/GraphicsCanvas.hpp>
#include <yq/graphicsQt/GraphicsScene.hpp>
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>
#include <yq/graphicsQt/GraphicsView.hpp>
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::SelectTool)

namespace yq::gluon {
    SelectTool::SelectTool(QObject* parent) : GraphicsTool(parent)
    {
        m_pen.setWidth(2);
        m_pen.setStyle(Qt::DashLine);
    }
    
    SelectTool::~SelectTool()
    {
    }
    
    void    SelectTool::deactivating() 
    {
        m_inDrag    = false;
    }

    QRectF  SelectTool::dragRect() const
    {
        QPointF tl(std::min(m_start.x(), m_mouse.x()), std::min(m_start.y(), m_mouse.y()));
        QPointF br(std::max(m_start.x(), m_mouse.x()), std::max(m_start.y(), m_mouse.y()));
        return QRectF(tl, br);
    }

    void    SelectTool::drawToolLayer(QPainter* painter, const QRectF&) 
    {
        if(!painter)
            return;
        if(!m_inDrag)
            return;
            
        painter->save();
        painter -> setBrush(Qt::NoBrush);
        painter -> setPen(m_pen);
        painter -> drawRect(dragRect());
        painter->restore();
    }
    
    void    SelectTool::mouseMoveEvent(QMouseEvent*evt) 
    {
        GraphicsView*   gv  = view();
        if(!gv)
            return ;
        if(!m_inDrag)
            return ;
            
        QPointF m   = gv -> mapToScene(evt -> position());
        if(m != m_mouse){
            m_mouse = m;
            update();
            invalidateToolLayer();
        }
        
        evt -> accept();
    }
    
    void    SelectTool::mousePressEvent(QMouseEvent*evt) 
    {
        GraphicsView*   gv  = view();
        if(!gv)
            return ;
        m_inDrag    = true;
        m_start     = gv -> mapToScene(evt -> position());
        m_mouse     = m_start;
        evt -> accept();
    }
    
    void    SelectTool::mouseReleaseEvent(QMouseEvent*evt) 
    {
        GraphicsView*   gv  = view();
        if(!gv)
            return ;
        if(!m_inDrag)
            return ;
        
        m_inDrag        = false;
        invalidateToolLayer();
        evt -> accept();
        
        GraphicsScene*  sc  = gv -> scene();
        if(!sc)
            return;
        
        GraphicsCanvas*  cvs  = canvas();
        if(!cvs)
            return ;

        cvs -> selectThese(sc->items(dragRect()));
    }
    
    void    SelectTool::wheelEvent(QWheelEvent*evt) 
    {
        if(m_inDrag){
            evt -> ignore();
        } else
            GraphicsTool::wheelEvent(evt);
    }

    void SelectTool::init_meta()
    {
        auto w = writer<SelectTool>();
        w.description("Selection Tool");
        w.icon(0, "yq/icon/tool/select.svg");
    }
}

#include "moc_SelectTool.cpp"
