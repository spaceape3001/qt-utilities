////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/Graph.hpp>
#include <QObject>

namespace yq::gluon {
    /*! \brief Information decoder for types of graphs
    
    
        This transforms the info-based graph document into a 
        gui-friendly manner (for the scene to digest)
    */
    class GraphCodec : public QObject {
        Q_OBJECT
    public:
    
        GraphCodec(QObject*parent=nullptr);
        GraphCodec(g::Document&&, QObject*parent=nullptr);
        
        void        set_document(g::Document&&);
        
        const g::Document&      document() const 
        { 
            return m_document; 
        }
    
    signals:
        void        codecChanged();
    
    private:
        g::Document         m_document;
    };

}
