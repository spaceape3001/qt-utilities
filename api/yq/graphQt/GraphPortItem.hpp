////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GPort.hpp>
#include <yq/graphQt/GraphItem.hpp>

namespace yq::gluon {
    class GraphPortItem : public GraphItem {
        GPort       m_data;
    public:
        GraphPortItem(GraphScene&, GPort);
        ~GraphPortItem();
    };
}
