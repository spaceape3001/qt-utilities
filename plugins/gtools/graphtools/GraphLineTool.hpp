////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>

namespace yq::gluon {
    class GraphLineTool : public GraphicsTool {
        YQ_OBJECTQ_DECLARE(GraphLineTool, GraphicsTool)
        Q_OBJECT
    public:
    
        GraphLineTool(QObject* parent=nullptr);
        ~GraphLineTool();
    
        static void init_meta();
    };
}
