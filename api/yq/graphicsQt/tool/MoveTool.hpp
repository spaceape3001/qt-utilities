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
    class MoveTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(MoveTool, GraphicsTool)
        Q_OBJECT
    public:
    
        MoveTool(QObject* parent=nullptr);
        ~MoveTool();
    
        static void init_meta();

    protected:
        virtual void    mouseMoveEvent(QMouseEvent*) override;
        virtual void    mousePressEvent(QMouseEvent*) override;
        virtual void    mouseReleaseEvent(QMouseEvent*) override;
        virtual void    wheelEvent(QWheelEvent*) override;
        virtual void    deactivating() override;
        
    private:
        bool            m_inDrag    = false;
        QPointF         m_start;
        
        struct D;
        std::vector<D>  m_items;
    };
}
