////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once



#include <yq/graph/GEdge.hpp>
#include <yq/graph/GLine.hpp>
#include <yq/graph/GNode.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <yq/graph/GPort.hpp>
#include <yq/graph/GShape.hpp>
#include <yq/graph/GText.hpp>
#include <yq/graphQt/GraphScene.hpp>
#include <yq/graphQt/GraphItem.hpp>

#include <yq/symbolQt/SymbolGraphicsItem.hpp>
#include <yq/typedef/vector2.hpp>

#include <QGraphicsPathItem>
#include <QGraphicsItemGroup>
#include <QGraphicsTextItem>

namespace yq::gluon {


#if 0
    struct XGSceneQt::Node : public gluon::SymbolGraphicsItem, public GraphItem  {
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
