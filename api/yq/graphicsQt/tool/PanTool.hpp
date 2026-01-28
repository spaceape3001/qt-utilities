////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>

namespace yq::gluon {
    class PanTool : public GraphicsTool {
        YQ_OBJECT_DECLARE(PanTool, GraphicsTool)
        Q_OBJECT
    public:
    
        PanTool(QObject* parent=nullptr);
        ~PanTool();
    
        static void init_meta();
    };
}
