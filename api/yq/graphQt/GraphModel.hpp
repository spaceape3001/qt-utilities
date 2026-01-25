////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graph/preamble.hpp>

namespace yq::gluon {
    class GraphModel : public QObject {
        Q_OBJECT
    public:
    
        GraphModel(QObject*parent=nullptr);
        GraphModel(const g::Document&, const QObject*parent=nullptr);
        ~GraphModel();
    
    private:
    
        void        _clear();
        void        _set(GraphDocument*);
    
        GraphDocument*      m_document  = nullptr;
    };
}


