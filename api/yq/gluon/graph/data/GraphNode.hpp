////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graph/data/GraphPinned.hpp>

namespace yq::gluon {
    class GraphNode : public GraphPinned {
        Q_OBJECT
    public:
        GraphNode(QObject* parent=nullptr);
        GraphNode(const g::Node&, QObject* parent=nullptr);
        ~GraphNode();
        
        g::Node     get() const;
        void        saveTo(g::Node&) const;
    };
}

