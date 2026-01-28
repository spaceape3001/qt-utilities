////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SelectTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECT_IMPLEMENT(yq::gluon::SelectTool)

namespace yq::gluon {
    SelectTool::SelectTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    SelectTool::~SelectTool()
    {
    }
    
    void SelectTool::init_meta()
    {
        auto w = writer<SelectTool>();
        w.description("Selection Tool");
        w.icon(0, "yq/icon/tool/select.svg");
    }
}

#include "moc_SelectTool.cpp"
