////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <yq/graphicsQt/GraphicsTool.hpp>
#include <yq/graphQt/GraphPointCapture.hpp>

#include <QPen>
#include <QPoint>
#include <QPointF>
#include <QRectF>
#include <QTransform>

class QGraphicsItem;

namespace yq::gluon {
    class GraphScene;
    class GraphView;
    class GraphCanvas;
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
    
        virtual void    activating() override;
        virtual void    deactivating() override;
        virtual void    drawToolLayer(QPainter*, const QRectF&) override;
        virtual void 	keyPressEvent(QKeyEvent*) override;
        virtual void 	keyReleaseEvent(QKeyEvent*) override;
        virtual void    mouseDoubleClickEvent(QMouseEvent*) override;
        virtual void    mouseMoveEvent(QMouseEvent*) override;
        virtual void    mousePressEvent(QMouseEvent*) override;
        virtual void    mouseReleaseEvent(QMouseEvent*) override;
        virtual void    wheelEvent(QWheelEvent*) override;

    private:
    
        enum class Mode {   // ie...state
            None,
            Move,
            Skip,
            PressNothing,
            PressNode,
            PressPort,
            PressLine,
            PressEdge,
            PressText,
            PressShape,
            Pan,
            Select
        };
        
        enum class F {
            PinGood,
            PinBad,
            InDrag,
            ValidPress,
            Transform,
            Last,
            SelectRect,
            OutlineRect
        };

        Mode                    m_mode      = Mode::None;
        Flags<F>                m_flags     = {};
        GraphCanvas*            m_canvas    = nullptr;
        GraphScene*             m_scene     = nullptr;
        GraphView*              m_view      = nullptr;


        //QRectF              m_selectRect;
        //QPen                m_selectPen;

        QPen                    m_badPen;
        GraphPointCapture       m_capture;          //!< Capture at last mouse press
        QPointF                 m_lastPosition;     //!< Last position (in screen/widget)
        QPointF                 m_lastPoint;        //!< Last position (in scene coordinates)
        QRectF                  m_outlineRect;
        QRectF                  m_pinRect;          //!< Current pin rectangle
        QRectF                  m_selectRect;
        QTransform              m_transform;        //!< Last viewport transform (inverted)
        
        struct {
            QPen                pen, use;
            //QRectF              rect;
            //bool                draw    = false;
        }                   m_outline;
        
        struct {
            QPen                good;
            QPen                bad;
            //QRectF              rect;
        }   m_port;
        
        
        struct {    
            QPen            pen;
            //QRectF          rect;
            //bool            draw    = false;
        } m_select;
        
        void            _cancel();
        bool            _check() const;
        void            _decruft();
        bool            _dragging(QSinglePointEvent*) const;
        QPointF         _last(QSinglePointEvent*);
        bool            _select(QGraphicsItem*);    // TRUE if this is a new selection
        bool            _tselect(QGraphicsItem*);   // TRUE if we're now selected
        void            _transform();
        bool            _wheel() const;
    
    
        void            noneMMove(QMouseEvent*);
        void            noneMRelease(QMouseEvent*);
        
        void            panMMove(QMouseEvent*);
        void            panMRelease(QMouseEvent*);
        
    
        void            moveNone(QMouseEvent*);
        void            nodeMove(QMouseEvent*);

    };
}
