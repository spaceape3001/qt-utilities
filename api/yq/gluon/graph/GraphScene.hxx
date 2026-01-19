////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graph/GraphScene.hpp>
#include <yq/gluon/graphics/GraphicsSymbolItem.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <QGraphicsItemGroup>

namespace yq::gluon {
    struct GraphScene::Item {
        Item();
        virtual ~Item();
        
        virtual QGraphicsItem*          qItem() = 0;
        virtual const QGraphicsItem*    qItem() const = 0;
    };

    struct GraphScene::Node : public GraphicsSymbolItem, public Item  {
        GNodeTemplateCPtr       m_template;
        // data....
        float                   m_size      = 64.;
        
        //  Node(const Node&);  // pending/TODO
        Node(const GNodeTemplateCPtr&, const QPointF&);
        //Node(const GNodeTemplateCPtr&, const GNodeData&);   // TODO
        //Node(const GNodeData&);   // TODO
        
        void    _init();
        virtual ~Node();

        SymbolCPtr  _symbol() const;


        virtual QGraphicsItem*          qItem() override { return this; }
        virtual const QGraphicsItem*    qItem() const override { return this; }
    };

#if 0
    struct XGSceneQt::Node : public gluon::GraphicsSymbolItem, public Item  {
        XGDocNode               m_data;
        QGraphicsRectItem*      m_box   = nullptr;
        QGraphicsTextItem*      m_text  = nullptr;
        
        //  Node(const Node&);  // pending/TODO
        Node(const XGDocNode&);
        Node(const XGNodeMeta&, const QPointF&);
        
        using gluon::GraphicsSymbolItem::build;
        
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
