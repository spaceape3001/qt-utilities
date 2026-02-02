////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GShape.hpp>
#include <yq/graphQt/GraphItem.hpp>

namespace yq::gluon {
    class GraphShapeItem : public GraphItem {
    public:
        
        GraphShapeItem(GraphScene&, GShape);
        virtual ~GraphShapeItem();

        //virtual QGraphicsItem*          qItem() { return nullptr; }
        //virtual const QGraphicsItem*    qItem() const { return nullptr; }
        
    private:
        GShape      m_data;
    };
    
}
