////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphPinned.hpp"

namespace yq::gluon {
    GraphPinned::GraphPinned(QObject* parent) : GraphBase(parent)
    {
    }
    
    GraphPinned::GraphPinned(const g::Pinned&v, QObject* parent) : GraphBase(v, parent)
    {
        for(const g::Pin& p : v.pins)
            new GraphPin(p, this);
    }
    
    GraphPinned::~GraphPinned()
    {
    }
    
    bool        GraphPinned::operator==(const GraphPinned&v) const
    {
        return GraphBase::operator==(v) && sameChildrenAs<GraphPin>(v);
    }
    
    g::Pinned           GraphPinned::get() const
    {
        g::Pinned ret;
        saveTo(ret);
        return ret;
    }
    
    void                GraphPinned::saveTo(g::Pinned&v) const
    {
        GraphBase::saveTo(v);
        foreachPin([&](GraphPin* p){
            g::Pin  v2  = p->get();
            v.pins.push_back(std::move(v2));
        });
    }
    
    std::vector<GraphPin*>   GraphPinned::pins() const
    {
        return childrenAs<GraphPin>();
    }
}

#include "moc_GraphPinned.cpp"
