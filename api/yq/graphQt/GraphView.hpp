////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/keywords.hpp>
#include <yq/graphicsQt/GraphicsView.hpp>

class QSinglePointEvent;

namespace yq::gluon {
    class GraphScene;
    struct GraphPointCapture;
    
    class GraphView : public GraphicsView {
        Q_OBJECT
    public:
        GraphView(QWidget*parent=nullptr);
        GraphView(GraphScene*, QWidget*parent=nullptr);
        ~GraphView();
        
        GraphScene* scene() { return m_scene; }
        const GraphScene* scene() const { return m_scene; }
        
        struct CaptureOptions;
        
        GraphPointCapture   capture(QSinglePointEvent*) const;
        GraphPointCapture   capture(QSinglePointEvent*, const CaptureOptions&) const;

        GraphPointCapture   capture(const QPoint&) const;
        GraphPointCapture   capture(const QPoint&, const CaptureOptions&) const;

        GraphPointCapture   capture(widget_k, const QPointF&) const;
        GraphPointCapture   capture(widget_k, const QPointF&, const CaptureOptions&) const;
        
    protected:
        void    dragEnterEvent(QDragEnterEvent*) override;
        void    dragLeaveEvent(QDragLeaveEvent*) override;
        void    dragMoveEvent(QDragMoveEvent*) override;
        void    dropEvent(QDropEvent*) override;

    private:
        GraphScene* const m_scene;
        QGraphicsItem*  m_dragItem  = nullptr;
    };
    
    struct GraphView::CaptureOptions {
        bool    edges   = false;
        bool    items   = false;
        bool    lines   = false;
        bool    nodes   = false;
        bool    ports   = false;
        bool    shapes  = false;
        bool    texts   = false;
    };
}
