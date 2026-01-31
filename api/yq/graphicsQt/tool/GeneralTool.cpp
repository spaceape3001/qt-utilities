////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GeneralTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::gluon::GeneralTool)

namespace yq::gluon {
    GeneralTool::GeneralTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    GeneralTool::~GeneralTool()
    {
    }
    
    void GeneralTool::init_meta()
    {
        auto w = writer<GeneralTool>();
        w.description("Generalion Tool");
        w.icon(0, "yq/icon/tool/select.svg");
    }
}

#include "moc_GeneralTool.cpp"
