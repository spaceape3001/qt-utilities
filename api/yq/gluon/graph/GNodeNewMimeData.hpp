////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GNodeTemplate.hpp>
#include <QMimeData>

namespace yq::gluon {
    class GNodeNewMimeData : public QMimeData {
        Q_OBJECT
    public:
        GNodeNewMimeData(const GNodeTemplateCPtr&);
        ~GNodeNewMimeData();
        
        const GNodeTemplateCPtr&    node() const { return m_node; }
        
    private:
        const GNodeTemplateCPtr   m_node;
    };
}
