////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <yq/graph/GGraph.hpp>
#include <yq/graphicsQt/GraphicsTool.hpp>
#include <yq/graphQt/GraphPointCapture.hpp>

#include <QPainterPath>
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
        virtual void    contextMenuEvent(QContextMenuEvent*) override;
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
            Select,
            DragNewEdge
        };
        
        enum class F {
            PinGood,
            InDrag,
            ValidPress,
            Transform,
            Last,
            PinDraw,
            SelectRect,
            OutlineRect,
            WantInput,
            WantOutput
        };

        Mode                    m_mode      = Mode::None;
        Flags<F>                m_flags     = {};
        GraphCanvas*            m_canvas    = nullptr;
        GraphScene*             m_scene     = nullptr;
        GraphView*              m_view      = nullptr;
        GGraph                  m_graph;

        QPen                    m_badPen;
        GraphPointCapture       m_capture;          //!< Capture at last mouse press
        GraphPointCapture       m_last;             //!< Capture at last mouse press
        QPen                    m_linePen;
        QPainterPath            m_linePath;
        QPen                    m_outlinePen;
        QRectF                  m_outlineRect;
        QPen                    m_pinPen;
        QRectF                  m_pinRect;          //!< Current pin rectangle
        QPen                    m_selectPen;
        QRectF                  m_selectRect;
        QTransform              m_transform;        //!< Last viewport transform (inverted)
        
        void            _cancel();
        bool            _check() const;
        void            _decruft();
        bool            _dragging(QSinglePointEvent*) const;
        QPointF         _last(QSinglePointEvent*);
        bool            _select(QGraphicsItem*);    // TRUE if already selected
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
