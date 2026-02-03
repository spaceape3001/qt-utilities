////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "EdgeConnectorTool.hpp"
#include <yq/graphicsQt/GraphicsToolMetaWriter.hpp>

YQ_OBJECTQ_IMPLEMENT(yq::gluon::EdgeConnectorTool)

namespace yq::gluon {
    EdgeConnectorTool::EdgeConnectorTool(QObject* parent) : GraphicsTool(parent)
    {
    }
    
    EdgeConnectorTool::~EdgeConnectorTool()
    {
    }

    void EdgeConnectorTool::init_meta()
    {
        auto w = writer<EdgeConnectorTool>();
        w.description("Edge Connector Tool");
        w.icon(0, "yq/icon/tool/connector.svg");
    }
}

#include "moc_EdgeConnectorTool.cpp"
