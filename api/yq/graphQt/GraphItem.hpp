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

    protected:
        GraphScene& m_scene;
    };
}
