////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GLine.hpp>
#include <yq/graphQt/GraphItem.hpp>
#include <QGraphicsPathItem>

namespace yq::gluon {

    class GraphLineItem : public QGraphicsPathItem, public GraphItem {
    public:
    
        GraphLineItem(GraphScene&, GLine);
        virtual ~GraphLineItem();
        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }

    private:
        GLine       m_data;
        
        void _init();
    };
}
