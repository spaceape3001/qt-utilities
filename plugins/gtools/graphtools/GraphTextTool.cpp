////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphTextTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::GraphTextTool)

namespace yq::gluon {
    GraphTextTool::GraphTextTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    GraphTextTool::~GraphTextTool()
    {
    }

    void GraphTextTool::init_meta()
    {
        auto w = writer<GraphTextTool>();
        w.description("Graph Text Tool");
        w.icon(0, "yq/icon/tool/text.svg");
    }
}

#include "moc_GraphTextTool.cpp"
