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
        if(!GraphName::operator==(other))
            return false;
        
        std::vector<GraphProperty*>     us      = properties();
        std::vector<GraphProperty*>     them    = other.properties();
        
        if(us.size() != them.size())
            return false;
        for(size_t n=0;n<us.size();++n){
            if(!(us[n]->operator==(*them[n])))
                return false;
        }
        return true;
    }

    std::vector<GraphProperty*> GraphBase::properties() const
    {
        std::vector<GraphProperty*>     ret;
        foreachProperty([&](GraphProperty* p){
            ret.push_back(p);
        });
        return ret;
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
