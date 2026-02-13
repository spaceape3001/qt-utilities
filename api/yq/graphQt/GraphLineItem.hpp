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

        auto& data() { return m_data; }
        const auto& data() const { return m_data; }
        gid_t   id() const { return m_data.id(); }

    private:
        GLine       m_data;
        
        void _init();
    };
}
