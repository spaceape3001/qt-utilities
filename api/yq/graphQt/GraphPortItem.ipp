////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphPortItem.hpp"

namespace yq::gluon {
    GraphPortItem::GraphPortItem(GraphScene& gs, GPort port) : GraphItem(gs), m_data(port)
    {
        // TODO... hookups
    }
    
    GraphPortItem::~GraphPortItem()
    {
    }
}
