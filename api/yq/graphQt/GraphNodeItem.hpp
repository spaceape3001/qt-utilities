////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/interface/PositionInterface.hpp>
#include <yq/graph/GNode.hpp>
#include <yq/graphQt/GraphItem.hpp>
#include <yq/symbolQt/SymbolGraphicsItem.hpp>
#include <yq/typedef/g_node_template.hpp>

namespace yq::gluon {
    class GraphNodeItem : public SymbolGraphicsItem, public GraphItem, public PositionInterface {
    public:
        //  Node(const Node&);  // pending/TODO
        GraphNodeItem(GraphScene&, GNode);
        
        virtual ~GraphNodeItem();

        void            position(set_k, const Vector2D&);
        void            position(set_k, const QPointF&) override;
        
        virtual QPointF  position() const override;


        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    
    private:
        GNodeTemplateCPtr       m_template;
        GNode                   m_data;
        
        void    _init();
        SymbolCPtr  _symbol() const;
        
        using PositionInterface::position;
        
    };
}
