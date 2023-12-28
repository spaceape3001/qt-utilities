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
        
        bool        operator==(const GraphPinned&) const;
        
        template <typename Pred>
        void foreachPin(Pred p) const
        {
            foreachChildAs<GraphPin, Pred>(std::move(p));
        }
        
        g::Pinned               get() const;
        void                    saveTo(g::Pinned&) const;
        std::vector<GraphPin*>  pins() const;
    };
}

