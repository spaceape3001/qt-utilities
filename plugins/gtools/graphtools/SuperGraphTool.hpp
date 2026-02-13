////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <yq/graphicsQt/GraphicsTool.hpp>

#include <QPen>
#include <QPoint>
#include <QPointF>
#include <QRectF>
#include <QTransform>

class QGraphicsItem;

namespace yq::gluon {
    class GraphItem;

    /*! \brief Super Graph Tool
    
        This is the super graph tool, meant to combine a few into a more seemless 
        (& less clicky) experience.
        
    */
    class SuperGraphTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(SuperGraphTool, GraphicsTool)
        Q_OBJECT
    public:
    
        SuperGraphTool(QObject* parent=nullptr);
        ~SuperGraphTool();
    
        static void init_meta();

    protected:
    
        void            cancel();
        virtual void    deactivating() override;
        virtual void    drawToolLayer(QPainter*, const QRectF&) override;
        virtual void 	keyPressEvent(QKeyEvent*) override;
        virtual void 	keyReleaseEvent(QKeyEvent*) override;
        virtual void    mouseDoubleClickEvent(QMouseEvent*) override;
        virtual void    mouseMoveEvent(QMouseEvent*) override;
        virtual void    mousePressEvent(QMouseEvent*) override;
        virtual void    mouseReleaseEvent(QMouseEvent*) override;
        virtual void    wheelEvent(QWheelEvent*) override;

        void            startPress(QMouseEvent*);
        void            moveNone(QMouseEvent*);
        void            panMove(QMouseEvent*);
        void            decruft();

    private:
        enum class Mode {   // ie...state
            None,
            Press,
            Pan
        };
        
        enum class F {
            PinGood,
            PinBad,
            SelectRect
        };

        Mode                m_mode  = Mode::None;
        Flags<F>            m_flags;

        QRectF              m_pinRect;
        QRectF              m_selectRect;
        QPen                m_selectPen;
        QPen                m_badPen;
        
        struct {
            QPen                pen;
            QRectF              rect;
            bool                draw    = false;
        }                   m_outline;
        
        struct {
            QPointF         last;
            QTransform      transform;
        } m_pan;
        
        
        bool        canWheel() const;
    };
}
