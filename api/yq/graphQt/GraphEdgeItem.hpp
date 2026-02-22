////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GEdge.hpp>
#include <yq/graphQt/GraphItem.hpp>
#include <QGraphicsPathItem>

namespace yq::gluon {

    class GraphEdgeItem : public QGraphicsPathItem, public GraphItem {
    public:
    
        GraphEdgeItem(GraphScene&, GEdge);
        virtual ~GraphEdgeItem();
        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }

        auto& data() { return m_data; }
        const auto& data() const { return m_data; }
        gid_t   id() const { return m_data.id(); }

        virtual bool is_edge() const override { return true; }

        virtual void update() override;

    private:
        GEdge       m_data;
        
        void _init();
    };
}
