////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>
#include <QPointF>
#include <QTransform>

namespace yq::gluon {
    class PanTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(PanTool, GraphicsTool)
        Q_OBJECT
    public:
    
        PanTool(QObject* parent=nullptr);
        ~PanTool();
    
        static void init_meta();

    protected:
        virtual void    mouseMoveEvent(QMouseEvent*) override;
        virtual void    mousePressEvent(QMouseEvent*) override;
        virtual void    mouseReleaseEvent(QMouseEvent*) override;
        virtual void    wheelEvent(QWheelEvent*) override;
        virtual void    deactivating() override;
        
    private:
        bool        m_inDrag    = false;
        QPointF     m_last;
    };
}
