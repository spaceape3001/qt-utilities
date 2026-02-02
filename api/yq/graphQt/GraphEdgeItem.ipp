////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphEdgeItem.hpp"

namespace yq::gluon {
    GraphEdgeItem::GraphEdgeItem(GraphScene& gs, GEdge gl) : GraphItem(gs), m_data(gl)
    {
    }
    
    GraphEdgeItem::~GraphEdgeItem()
    {
    }
    
    void GraphEdgeItem::_init()
    {
    }
}
