////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsView.hpp>

namespace yq::gluon {
    class GraphScene;
    
    class GraphView : public GraphicsView {
        Q_OBJECT
    public:
        GraphView(QWidget*parent=nullptr);
        GraphView(GraphScene*, QWidget*parent=nullptr);
        ~GraphView();
        
        GraphScene* scene() { return m_scene; }
        const GraphScene* scene() const { return m_scene; }
        
    protected:
        void    dragEnterEvent(QDragEnterEvent*) override;
        void    dragLeaveEvent(QDragLeaveEvent*) override;
        void    dragMoveEvent(QDragMoveEvent*) override;
        void    dropEvent(QDropEvent*) override;

    private:
        GraphScene* const m_scene;
        QGraphicsItem*  m_dragItem  = nullptr;
    };
}
