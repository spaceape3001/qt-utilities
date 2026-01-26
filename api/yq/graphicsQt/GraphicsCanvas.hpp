////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/app/SubWindow.hpp>
#include <yq/typedef/meta_id.hpp>

namespace yq::gluon {
    class GraphicsScene;
    class GraphicsView;
    class GraphicsTool;
    class GraphicsToolMeta;
    
    class GraphicsCanvas : public SubWindow {
        Q_OBJECT
    public:
    
        GraphicsCanvas(QWidget*parent=nullptr);
        GraphicsCanvas(GraphicsScene*, QWidget*parent=nullptr);
        GraphicsCanvas(GraphicsView*, QWidget*parent=nullptr);
        ~GraphicsCanvas();
        
        void                    setEdgePen(QPen);
        void                    setPaperBrush(QBrush);
        void                    setBackgroundBrush(QBrush);

        GraphicsScene*          scene() { return m_scene; }
        const GraphicsScene*    scene() const { return m_scene; }
        
        GraphicsView*           view() { return m_view; }
        const GraphicsView*     view() const { return m_view; }
        
        uint64_t    currentTool() const;
        
        
    signals:
        void        toolChanged(uint64_t);
        
    public slots:
        void        setTool(uint64_t);

    private:
        GraphicsScene* const    m_scene;
        GraphicsView* const     m_view;
        
        std::map<meta_id_t, GraphicsTool*>   m_tools;
    };
}
