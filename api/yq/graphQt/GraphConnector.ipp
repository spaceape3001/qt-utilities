////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphConnector.hpp"

namespace yq::gluon {
    GraphConnector::GraphConnector()
    {
    }
    
    GraphConnector::~GraphConnector()
    {
    }

    void        GraphConnector::connect(gid_t i)
    {
        m_connected += i;
    }

    bool    GraphConnector::connected(gid_t i) const
    {
        return m_connected.contains(i);
    }

    void        GraphConnector::disconnect(gid_t i)
    {
        m_connected -= i;
    }
}
