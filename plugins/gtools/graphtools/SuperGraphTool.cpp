////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "SuperGraphTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::SuperGraphTool)

namespace yq::gluon {
    SuperGraphTool::SuperGraphTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    SuperGraphTool::~SuperGraphTool()
    {
    }

    void SuperGraphTool::init_meta()
    {
        auto w = writer<SuperGraphTool>();
        w.description("Super Graph Tool");
        w.icon(0, "yq/icon/tool/super.svg");
    }
}

#include "moc_SuperGraphTool.cpp"
