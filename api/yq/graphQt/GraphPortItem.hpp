////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GPort.hpp>
#include <yq/graphQt/GraphItem.hpp>

namespace yq::gluon {
    class GraphPortItem : public GraphItem {
    public:
        GraphPortItem(GraphScene&, GPort, QGraphicsItem*it);
        ~GraphPortItem();

        virtual QGraphicsItem*          qItem() { return m_item; }
        virtual const QGraphicsItem*    qItem() const { return m_item; }

    private:
        GPort               m_data;
        QGraphicsItem*      m_item = nullptr;
    };
}
