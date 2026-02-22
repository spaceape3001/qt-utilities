////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

class QGraphicsItem;

namespace yq::gluon {
    class GraphScene;
    
    class GraphItem {
    public:
    
        GraphItem(GraphScene&);
        virtual ~GraphItem();
        
        virtual QGraphicsItem*          qItem() { return nullptr; }
        virtual const QGraphicsItem*    qItem() const { return nullptr; }

        GraphScene& scene() { return m_scene; }
        const GraphScene& scene() const { return m_scene; }

        //! Update/Refresh the graphics item from any model changes
        virtual void update(){}
        
        virtual bool is_edge() const { return false; }
        virtual bool is_line() const { return false; }
        virtual bool is_node() const { return false; }
        virtual bool is_port() const { return false; }
        virtual bool is_shape() const { return false; }
        virtual bool is_text() const { return false; }

        bool is_dirty() const { return m_dirty; }

    protected:
        GraphScene& m_scene;
        bool        m_dirty = false;
    };
}
