////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "PanTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::gluon::PanTool)

namespace yq::gluon {
    PanTool::PanTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    PanTool::~PanTool()
    {
    }
    
    void PanTool::init_meta()
    {
        auto w = writer<PanTool>();
        w.description("Pan Tool");
        w.icon(0, "yq/icon/tool/pan.svg");
    }
}

#include "moc_PanTool.cpp"
