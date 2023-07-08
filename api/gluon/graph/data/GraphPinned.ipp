////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

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
        std::vector<GraphPin*>   ret;
        foreachPin([&](GraphPin* p){
            ret.push_back(p);
        });
        return ret;
    }
}
