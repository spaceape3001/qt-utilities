////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>

namespace yq::gluon {
    class SelectTool : public GraphicsTool {
        YQ_OBJECT_DECLARE(SelectTool, GraphicsTool)
        Q_OBJECT
    public:
    
        SelectTool(QObject* parent=nullptr);
        ~SelectTool();
    
        static void init_meta();
    };
}
