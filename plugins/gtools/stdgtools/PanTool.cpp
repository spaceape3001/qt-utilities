////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>
#include "PanTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>
#include <yq/graphicsQt/GraphicsView.hpp>
#include <QMouseEvent>
#include <QWheelEvent>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::PanTool)

namespace yq::gluon {
    PanTool::PanTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    PanTool::~PanTool()
    {
    }
    
    void    PanTool::deactivating() 
    {
        m_inDrag    = false;
    }

    void    PanTool::mouseMoveEvent(QMouseEvent* evt) 
    {
        GraphicsView*   gv  = view();
        if(!gv)
            return ;
        if(!m_inDrag)
            return ;

        QTransform      t   = gv -> viewportTransform().inverted();
            
        QPointF     cur = t.map(evt -> position());
        QPointF     del = cur - m_last;
        m_last          = cur;
        
        gv -> translate(del.x(), del.y());
        evt -> accept();
    }
    
    void    PanTool::mousePressEvent(QMouseEvent* evt)
    {
        GraphicsView*   gv  = view();
        if(!gv)
            return ;

        m_inDrag    = true;
        QTransform      t   = gv -> viewportTransform().inverted();


        m_last      = t.map(evt -> position());
        evt -> accept();
    }
    
    void    PanTool::mouseReleaseEvent(QMouseEvent*evt) 
    {
        deactivating();
        evt -> accept();
    }

    void    PanTool::wheelEvent(QWheelEvent*evt) 
    {
        if(m_inDrag){
            evt -> ignore();
        } else
            GraphicsTool::wheelEvent(evt);
    }

    void PanTool::init_meta()
    {
        auto w = writer<PanTool>();
        w.description("Pan Tool");
        w.icon(0, "yq/icon/tool/pan.svg");
    }
}

#include "moc_PanTool.cpp"
