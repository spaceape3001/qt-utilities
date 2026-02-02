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
        
    private:
        GText       m_data;
    };
}
