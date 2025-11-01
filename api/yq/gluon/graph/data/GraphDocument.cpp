////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/graph/data/GraphDocument.hpp>

namespace yq::gluon {
    GraphDocument::GraphDocument(QObject* parent) : GraphBase(parent)
    {
    }
    
    GraphDocument::GraphDocument(const g::Document&v, QObject* parent) : GraphBase(v, parent)
    {
        for(const auto& gg : v.graphs)
            new GraphGraph(gg, this);
    }
    
    GraphDocument::~GraphDocument()
    {
    }
    
    bool GraphDocument::operator==(const GraphDocument&v) const
    {
        return GraphBase::operator==(v) && sameChildrenAs<GraphGraph>(v);
    }
    
    
    g::Document     GraphDocument::get() const
    {
        g::Document ret;
        saveTo(ret);
        return ret;
    }
    
    void            GraphDocument::saveTo(g::Document&v) const
    {
        GraphBase::saveTo(v);
        foreachGraph([&](GraphGraph* gg){
            g::Graph    v2  = gg->get();
            v.graphs.push_back(v2);
        });
    }
    
    std::vector<GraphGraph*>     GraphDocument::graphs() const
    {
        return childrenAs<GraphGraph>();
    }
}

#include "moc_GraphDocument.cpp"
