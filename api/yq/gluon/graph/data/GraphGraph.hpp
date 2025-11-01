////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graph/data/GraphPinned.hpp>
#include <gluon/graph/data/GraphNode.hpp>
#include <gluon/graph/data/GraphEdge.hpp>

namespace yq::gluon {
    class GraphGraph : public GraphPinned {
        Q_OBJECT
    public:
        GraphGraph(QObject* parent=nullptr);
        GraphGraph(const g::Graph&, QObject* parent=nullptr);
        ~GraphGraph();
        
        bool operator==(const GraphGraph&) const;
        
        g::Graph    get() const;
        void        saveTo(g::Graph&) const;
        
        template <typename Pred>
        void foreachEdge(Pred p) const
        {
            foreachChildAs<GraphEdge, Pred>(std::move(p));
        }

        std::vector<GraphEdge*>  edges() const;
        
        template <typename Pred>
        void foreachNode(Pred p) const
        {
            foreachChildAs<GraphNode, Pred>(std::move(p));
        }
        
        std::vector<GraphNode*>  nodes() const;
    };

}
