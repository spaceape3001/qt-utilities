////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphPortItem.hpp"
#include <yq/graphQt/GraphScene.hpp>

namespace yq::gluon {
    GraphPortItem::GraphPortItem(GraphScene& gs, GPort port, QGraphicsItem*it) : GraphItem(gs), m_data(port), m_item(it)
    {
        // TODO... hookups
    }
    
    GraphPortItem::~GraphPortItem()
    {
    }

    void    GraphPortItem::dirty(const DirtyOptions& opts)
    {
        m_scene.dirty(m_data.id());
        if(opts.edges){
            for(GEdge e : m_data.edges())
                m_scene.dirty(e.id());
        }
    }

    void    GraphPortItem::update() 
    {
        
    }
}
