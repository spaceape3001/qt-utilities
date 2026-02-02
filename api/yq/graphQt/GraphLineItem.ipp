////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphLineItem.hpp"

namespace yq::gluon {
    GraphLineItem::GraphLineItem(GraphScene& gs, GLine gl) : GraphItem(gs), m_data(gl)
    {
    }
    
    GraphLineItem::~GraphLineItem()
    {
    }
    
    void GraphLineItem::_init()
    {
    }
}
