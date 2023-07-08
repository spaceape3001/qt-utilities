////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graph/data/GraphBase.hpp>
#include <gluon/graph/data/GraphPin.hpp>

namespace yq::gluon {
    class GraphPinned : public GraphBase {
        Q_OBJECT
    public:
        GraphPinned(QObject* parent=nullptr);
        GraphPinned(const g::Pinned&, QObject* parent=nullptr);
        ~GraphPinned();
        
        template <typename Pred>
        void foreachPin(Pred p) const
        {
            for(QObject* obj : children()){
                GraphPin*   pin = qobject_cast<GraphPin*>(obj);
                if(pin){
                    p(pin);
                }
            }
        }
        
        g::Pinned               get() const;
        void                    saveTo(g::Pinned&) const;
        std::vector<GraphPin*>  pins() const;
    };
}

