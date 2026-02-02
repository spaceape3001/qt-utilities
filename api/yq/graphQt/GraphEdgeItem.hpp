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

    private:
        GEdge       m_data;
        
        void _init();
    };
}
