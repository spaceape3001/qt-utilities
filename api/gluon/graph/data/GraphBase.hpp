////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/Graph.hpp>
#include <gluon/graph/data/GraphName.hpp>
#include <gluon/graph/data/GraphProperty.hpp>
#include <QList>

namespace yq::gluon {
    class GraphBase : public GraphName {
        Q_OBJECT
    public:
        GraphBase(QObject* parent=nullptr);
        GraphBase(const g::Base&, QObject* parent=nullptr);
        ~GraphBase();
        
        bool    operator==(const GraphBase&) const;
        
        template <typename Q>
        std::vector<Q*>   childrenAs() const
        {
            std::vector<Q*> ret;
            for(QObject* obj : children()){
                Q*  q   = qobject_cast<Q*>(obj);
                if(q)
                    ret.push_back(q);
            }
            return ret;
        }
        
        
        template <typename Q>
        bool    sameChildrenAs(const GraphBase& other) const
        {
            auto us     = childrenAs<Q>();
            auto them   = other.childrenAs<Q>();
            if(us.size() != them.size())
                return false;
            for(size_t n=0;n<us.size();++n){
                if(!(us[n]->operator==(*them[n])))
                    return false;
            }
            return true;
        }
        
        
        template <typename Q, typename Pred>
        void    foreachChildAs(Pred pred) const
        {
            for(QObject* obj : children()){
                Q*  q    = qobject_cast<Q*>(obj);
                if(q){
                    pred(q);
                }
            }
        }

        template <typename Pred>
        void    foreachProperty(Pred p) const
        {
            foreachChildAs<GraphProperty, Pred>(std::move(p));
        }
        
         
        std::vector<GraphProperty*> properties() const;
        
        g::Base get() const;
        void    saveTo(g::Base&) const;
    };
}

