////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <graph/Graph.hpp>
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
        
        template <typename Pred>
        void    foreachProperty(Pred p) const
        {
            for(QObject* obj : children()){
                GraphProperty*  prop    = qobject_cast<GraphProperty*>(obj);
                if(prop){
                    p(prop);
                }
            }
        }
        
        std::vector<GraphProperty*> properties() const;
        
        g::Base get() const;
        void    saveTo(g::Base&) const;
    };
}

