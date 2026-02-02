////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>
#include <QPen>
#include <QPointF>

namespace yq::gluon {
    class SelectTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(SelectTool, GraphicsTool)
        Q_OBJECT
    public:
    
        SelectTool(QObject* parent=nullptr);
        ~SelectTool();
    
        static void init_meta();

        QRectF  dragRect() const;

    protected:

        virtual void    mouseMoveEvent(QMouseEvent*) override;
        virtual void    mousePressEvent(QMouseEvent*) override;
        virtual void    mouseReleaseEvent(QMouseEvent*) override;
        virtual void    wheelEvent(QWheelEvent*) override;
        virtual void    deactivating() override;
        virtual void    drawToolLayer(QPainter*, const QRectF&) override;
        
    private:
        QPointF     m_start, m_mouse;
        bool        m_inDrag    = false;
        QPen        m_pen;
    };
}
