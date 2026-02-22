////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphEdgeItem.hpp"
#include "GraphScene.hpp"
#include <yq/graph/GEdgeData.hpp>

namespace yq::gluon {
    GraphEdgeItem::GraphEdgeItem(GraphScene& gs, GEdge gl) : GraphItem(gs), m_data(gl)
    {
        _init();
    }
    
    GraphEdgeItem::~GraphEdgeItem()
    {
    }
    
    void GraphEdgeItem::_init()
    {
        update();
    }

    void GraphEdgeItem::update() 
    {
        GBase       src = m_data.source();
        GBase       tgt = m_data.target();
        if(const GEdgeData* ge = m_data.data()){
            QPainterPath    pp  = m_scene.path_for({src.id(), ge->waypoints, tgt.id()});
            setPath(pp);
        }
    }
}
