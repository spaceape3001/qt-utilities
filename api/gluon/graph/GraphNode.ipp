////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GraphNode.hpp"

namespace yq::gluon {
    GraphNode::GraphNode(QObject* parent) : GraphPinned(parent)
    {
    }
    
    GraphNode::GraphNode(const g::Node&v, QObject* parent) : GraphPinned(v, parent)
    {
    }
    
    GraphNode::~GraphNode()
    {
    }
    
    g::Node     GraphNode::get() const
    {
        g::Node ret;
        saveTo(ret);
        return ret;
    }
    
    void        GraphNode::saveTo(g::Node&v) const
    {
        GraphPinned::saveTo(v);
    }
}
