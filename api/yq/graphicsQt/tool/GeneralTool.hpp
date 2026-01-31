////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsTool.hpp>

namespace yq::gluon {

    //! General purpose select & move tool
    class GeneralTool : public GraphicsTool {
        YQ_OBJECT_DECLARE(GeneralTool, GraphicsTool)
        Q_OBJECT
    public:
    
        GeneralTool(QObject* parent=nullptr);
        ~GeneralTool();
    
        static void init_meta();
    };
}
