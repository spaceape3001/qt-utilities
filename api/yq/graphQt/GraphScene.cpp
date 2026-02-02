////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>

#include "GraphNodeItem.hpp"
#include "GraphEdgeItem.hpp"
#include "GraphLineItem.hpp"
#include "GraphPortItem.hpp"
#include "GraphScene.hpp"
#include "GraphShapeItem.hpp"
#include "GraphTextItem.hpp"

#include <yq/gluon/core/upoint.hpp>
#include <yq/gluon/core/uvector.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/symbol/Symbol.hpp>

namespace yq::gluon {

    GraphScene::GraphScene(GGraph gph, QObject*parent) : GraphicsScene(parent), m_graph(gph)
    {
        if(!gph)
            gph = GGraph(CREATE);
        set(gph);
        //makeCheckerboardBackgroundBrush();    // not working well
    }
    
    GraphScene::GraphScene(QObject*parent) : GraphScene(GGraph(), parent)
    {
    }
    
    GraphScene::~GraphScene()
    {
        clear();
    }

    GraphItem*   GraphScene::add(GBase gb)
    {
        if(!gb)
            return nullptr;
        if(gb.document() != m_graph.document())
            return nullptr;
            
        if(m_items.contains(gb.id()))
            return nullptr;
            
        GraphItem*   ret = nullptr;
            
        if(GEdge ge = (GEdge) gb)
            ret = new GraphEdgeItem(*this, ge);
        if(GLine gl = (GLine) gb)
            ret = new GraphLineItem(*this, gl);
        if(GNode gn = (GNode) gb)
            ret = new GraphNodeItem(*this, gn);
        if(GPort gp = (GPort) gb)
            ret = new GraphPortItem(*this, gp); 
        if(GShape gs = (GShape) gs)
            ret = new GraphShapeItem(*this, gs);
        if(GText gt = (GText) gb)
            ret = new GraphTextItem(*this, gt);

        if(ret){
            if(QGraphicsItem* it = ret->qItem()){ [[likely]]
                addItem(it);
            } else {
                m_notQt.push_back(ret);
            }
            m_items[gb.id()]    = ret;
        }
        return ret;
    }

    GraphNodeItem*    GraphScene::add(const GNodeTemplateCPtr& gnt, const QPointF& pt)
    {
        if(!gnt)    
            return nullptr;
            
        GNode   node    = m_graph.node(CREATE, *gnt);
        node.position(SET, yVector(pt));
        
        GraphNodeItem* gni  = static_cast<GraphNodeItem*>(add(node));
        
        //  And... the ports go here
        
        return gni;
    }
    
    void    GraphScene::clear()
    {
        m_items.clear();
        GraphicsScene::clear();
        for(GraphItem* it : m_notQt)
            delete it;
        m_notQt.clear();
    }

    GGraph      GraphScene::get() const
    {
        return m_graph;
    }

    void        GraphScene::set(GGraph g)
    {
        if(!g)
            return ;
        m_graph = g;
        clear();
        for(GBase b : g.children())
            add(b);
    }

    void    GraphScene::updateConnected(GNode)
    {
        // TODO
    }

    
}

#include "GraphEdgeItem.ipp"
#include "GraphItem.ipp"
#include "GraphLineItem.ipp"
#include "GraphNodeItem.ipp"
#include "GraphPortItem.ipp"
#include "GraphShapeItem.ipp"
#include "GraphTextItem.ipp"
#include "moc_GraphScene.cpp"
#include "moc_GraphTextItem.cpp"

