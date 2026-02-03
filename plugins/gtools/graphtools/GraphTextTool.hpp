////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>

namespace yq::gluon {
    class GraphTextTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(GraphTextTool, GraphicsTool)
        Q_OBJECT
    public:
    
        GraphTextTool(QObject* parent=nullptr);
        ~GraphTextTool();
    
        static void init_meta();
    };
}
