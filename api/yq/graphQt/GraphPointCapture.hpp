////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <QPointF>

class QGraphicsItem;

namespace yq::gluon {
    class GraphItem;
    class GraphEdgeItem;
    class GraphLineItem;
    class GraphNodeItem;
    class GraphPortItem;
    class GraphShapeItem;
    class GraphTextItem;
    
    struct GraphPointCapture {
    
        //! First edge encountered (if searching)
        GraphEdgeItem*      edge    = nullptr;
        
        //! Graph ID encountered
        //uint64_t            gid     = 0;
        
        //! Top/First item encountered (if searching)
        //GraphItem*          item    = nullptr;
        
        //! First line item encountered (if searching)
        GraphLineItem*      line    = nullptr;
        
        //! First node encountered (if searching)
        GraphNodeItem*      node    = nullptr;
        
        //! Point as mapped into the scene
        QPointF             point;     
        
        //! Point as provided (ie, the screen/widget)
        QPointF             position; 
        
        //! First port encountered (if searching)
        GraphPortItem*      port    = nullptr;
        
        //! First graphics item encountered
        QGraphicsItem*      qItem   = nullptr;
        
        //! First shape item encountered (if searching)
        GraphShapeItem*     shape   = nullptr;
        
        //! First text item encountered (if searching)
        GraphTextItem*      text    = nullptr;
    };
}
