////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/container/Set.hpp>
#include <yq/graph/GBase.hpp>

namespace yq::gluon {
    class GraphConnector {
    public:

        const auto& connected() const { return m_connected; }
        bool        connected(gid_t) const;
        void        disconnect(gid_t);
        void        connect(gid_t);
    
    protected:
        GraphConnector();
        ~GraphConnector();
    
    private:
        Set<gid_t>  m_connected;
    };
}
