////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphModel.hpp"
#include "data/GraphDocument.hpp"

namespace yq::gluon {
    GraphModel::GraphModel(QObject*parent) : QObject(parent)
    {
        _set(new GraphDocument(this));
    }
    
    GraphModel::GraphModel(const g::Document&doc, const QObject*parent)
    {
        _set(new GraphDocument(doc, this));
    }
    
    GraphModel::~GraphModel()
    {
    }

    void        GraphModel::_clear()
    {
        if(m_document)
            delete m_document;
        m_document  = nullptr;
    }
    
    void        GraphModel::_set(GraphDocument* doc)
    {
        m_document      = doc;
    }
}

#include "moc_GraphModel.cpp"
