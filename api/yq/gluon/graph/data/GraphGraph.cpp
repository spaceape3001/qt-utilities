////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphGraph.hpp"

namespace yq::gluon {
    GraphGraph::GraphGraph(QObject* parent) : GraphPinned(parent)
    {
    }
    
    GraphGraph::GraphGraph(const g::Graph&v, QObject* parent) : GraphPinned(v, parent)
    {
        for(auto& n : v.nodes)
            new GraphNode(n, this);
        for(auto& e : v.edges)
            new GraphEdge(e, this);
    }
    
    GraphGraph::~GraphGraph()
    {
    }
    
    
    bool GraphGraph::operator==(const GraphGraph&v) const
    {
        return GraphPinned::operator==(v) && sameChildrenAs<GraphNode>(v) && sameChildrenAs<GraphEdge>(v);
    }
    
    
    g::Graph    GraphGraph::get() const
    {
        g::Graph    ret;
        saveTo(ret);
        return ret;
    }
    
    void        GraphGraph::saveTo(g::Graph&v) const
    {
        GraphPinned::saveTo(v);
        foreachNode([&](GraphNode* p){
            g::Node  v2  = p->get();
            v.nodes.push_back(std::move(v2));
        });
        foreachEdge([&](GraphEdge* p){
            g::Edge  v2  = p->get();
            v.edges.push_back(std::move(v2));
        });
    }
    

    std::vector<GraphEdge*>  GraphGraph::edges() const
    {
        return childrenAs<GraphEdge>();
    }
    
    
    std::vector<GraphNode*>  GraphGraph::nodes() const
    {
        return childrenAs<GraphNode>();
    }
}

#include "moc_GraphGraph.cpp"

