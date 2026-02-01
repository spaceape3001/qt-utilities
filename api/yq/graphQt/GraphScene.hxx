////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once


#include <yq/gluon/interface/PositionInterface.hpp>

#include <yq/graph/GEdge.hpp>
#include <yq/graph/GLine.hpp>
#include <yq/graph/GNode.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <yq/graph/GPort.hpp>
#include <yq/graph/GShape.hpp>
#include <yq/graph/GText.hpp>
#include <yq/graphQt/GraphScene.hpp>

#include <yq/symbolQt/SymbolGraphicsItem.hpp>
#include <yq/typedef/vector2.hpp>

#include <QGraphicsPathItem>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>

namespace yq::gluon {
    struct GraphScene::Item {
        GraphScene& m_scene;
        Item(GraphScene&);
        virtual ~Item();
        
        virtual QGraphicsItem*          qItem() { return nullptr; }
        virtual const QGraphicsItem*    qItem() const { return nullptr; }
    };

    struct GraphScene::Edge : public QGraphicsPathItem, public Item {
        GEdge       m_data;
        
        void _init();
        
        Edge(GraphScene&, GEdge);
        virtual ~Edge();
        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };

    struct GraphScene::Line : public QGraphicsPathItem, public Item {
        GLine       m_data;
        
        void _init();

        Line(GraphScene&, GLine);
        virtual ~Line();
        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };

    struct GraphScene::Node : public SymbolGraphicsItem, public Item, public PositionInterface {
        GNodeTemplateCPtr       m_template;
        GNode                   m_data;
        
        //  Node(const Node&);  // pending/TODO
        Node(GraphScene&, GNode);
        //Node(const GNodeTemplateCPtr&, const GNodeData&);   // TODO
        //Node(const GNodeData&);   // TODO
        
        void    _init();
        virtual ~Node();

        SymbolCPtr  _symbol() const;
        
        using PositionInterface::position;
        
        void            position(set_k, const Vector2D&);
        void            position(set_k, const QPointF&) override;
        
        virtual QPointF  position() const override;


        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };

    struct GraphScene::Port : public Item {
        GPort       m_data;
        
        Port(GPort);
        virtual ~Port(){}
    };

    struct GraphScene::Shape : public Item {
        GShape      m_data;
        
        Shape(GShape);
        virtual ~Shape(){}
    };

    struct GraphScene::Text : public QGraphicsTextItem, public Item {
        GText       m_data;
        
        Text(GText);
        virtual ~Text(){}

        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };


#if 0
    struct XGSceneQt::Node : public gluon::SymbolGraphicsItem, public Item  {
        XGDocNode               m_data;
        QGraphicsRectItem*      m_box   = nullptr;
        QGraphicsTextItem*      m_text  = nullptr;
        
        //  Node(const Node&);  // pending/TODO
        Node(const XGDocNode&);
        Node(const XGNodeMeta&, const QPointF&);
        
        using gluon::SymbolGraphicsItem::build;
        
        void    build(std::string_view sym={});
        virtual ~Node();

        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };
    
    struct XGSceneQt::Text : public QGraphicsItemGroup, public Item {
        XGDocText               m_data;
        QGraphicsRectItem*      m_box   = nullptr;
        QGraphicsTextItem*      m_text  = nullptr;

        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };
    
    struct XGSceneQt::Line : public QGraphicsPathItem, public Item {
        XGDocLine               m_data;

        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };
    
    struct XGSceneQt::Edge : public QGraphicsPathItem, public Item {
        Node*                   m_source   = nullptr;
        Node*                   m_target   = nullptr;
        XGDocEdge               m_data;

        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };
#endif
}
