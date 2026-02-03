////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>

namespace yq::gluon {
    class EdgeConnectorTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(EdgeConnectorTool, GraphicsTool)
        Q_OBJECT
    public:
    
        EdgeConnectorTool(QObject* parent=nullptr);
        ~EdgeConnectorTool();
    
        static void init_meta();
    };
}
