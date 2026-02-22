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

        auto& data() { return m_data; }
        const auto& data() const { return m_data; }
        
        gid_t   id() const { return m_data.id(); }
        virtual bool is_port() const override { return true; }
        
        virtual void    update() override;

        struct DirtyOptions {
            bool        edges   = false;
        };
        
        void    dirty(const DirtyOptions&);

    private:
        GPort               m_data;
        QGraphicsItem*      m_item = nullptr;
    };
}
