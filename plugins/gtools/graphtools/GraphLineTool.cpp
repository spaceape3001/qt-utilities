////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphLineTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::GraphLineTool)

namespace yq::gluon {
    GraphLineTool::GraphLineTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    GraphLineTool::~GraphLineTool()
    {
    }

    void GraphLineTool::init_meta()
    {
        auto w = writer<GraphLineTool>();
        w.description("Graph Line Tool");
        w.icon(0, "yq/icon/tool/line.svg");
    }
}

#include "moc_GraphLineTool.cpp"
