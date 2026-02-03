////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphPortItem.hpp"

namespace yq::gluon {
    GraphPortItem::GraphPortItem(GraphScene& gs, GPort port, QGraphicsItem*it) : GraphItem(gs), m_data(port), m_item(it)
    {
        // TODO... hookups
    }
    
    GraphPortItem::~GraphPortItem()
    {
    }
}
