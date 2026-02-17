////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GText.hpp>
#include <yq/graphQt/GraphItem.hpp>
#include <QGraphicsTextItem>

namespace yq::gluon {
    class GraphTextItem : public QGraphicsTextItem, public GraphItem {
        Q_OBJECT
    public:
        GraphTextItem(GraphScene&, GText);
        virtual ~GraphTextItem();

        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }

        auto& data() { return m_data; }
        const auto& data() const { return m_data; }
        gid_t   id() const { return m_data.id(); }
        virtual bool is_text() const override { return true; }
        
    private:
        GText       m_data;
    };
}
