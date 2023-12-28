////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GraphBase.hpp"

namespace yq::gluon {
    GraphBase::GraphBase(QObject* parent) : GraphName(parent)
    {
    }
    
    GraphBase::GraphBase(const g::Base& v, QObject* parent) : GraphName(v, parent)
    {
        for(const g::Property& p : v.properties)
            new GraphProperty(p, this);
    }
    
    GraphBase::~GraphBase()
    {
    }

    bool    GraphBase::operator==(const GraphBase&other) const
    {
        return GraphName::operator==(other) && sameChildrenAs<GraphProperty>(other);
    }

    std::vector<GraphProperty*> GraphBase::properties() const
    {
        return childrenAs<GraphProperty>();
    }

    g::Base GraphBase::get() const
    {
        g::Base ret;
        saveTo(ret);
        return ret;
    }
    
    void    GraphBase::saveTo(g::Base&v) const
    {
        GraphName::saveTo(v);
        v.properties.clear();
        foreachProperty([&](GraphProperty* p){
            g::Property     v2 = p -> get();
            v.properties.push_back(std::move(v2));
        });
    }
}
