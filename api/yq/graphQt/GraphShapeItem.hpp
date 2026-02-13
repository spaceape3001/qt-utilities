////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GShape.hpp>
#include <yq/graphQt/GraphItem.hpp>

namespace yq::gluon {
    class GraphShapeItem : public GraphItem {
    public:
        
        GraphShapeItem(GraphScene&, GShape);
        virtual ~GraphShapeItem();

        //virtual QGraphicsItem*          qItem() { return nullptr; }
        //virtual const QGraphicsItem*    qItem() const { return nullptr; }
        
        auto& data() { return m_data; }
        const auto& data() const { return m_data; }
        gid_t   id() const { return m_data.id(); }

    private:
        GShape      m_data;
    };
    
}
