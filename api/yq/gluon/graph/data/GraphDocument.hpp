////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graph/data/GraphBase.hpp>
#include <yq/gluon/graph/data/GraphGraph.hpp>

namespace yq::gluon {
    class GraphDocument : public GraphBase {
        Q_OBJECT
    public:
        GraphDocument(QObject* parent=nullptr);
        GraphDocument(const g::Document&, QObject* parent=nullptr);
        ~GraphDocument();
        
        bool operator==(const GraphDocument&) const;
        
        g::Document     get() const;
        void            saveTo(g::Document&) const;
        
        template <typename Pred>
        void            foreachGraph(Pred p) const
        {
            foreachChildAs<GraphGraph>(std::move(p));
        }
        
        std::vector<GraphGraph*>     graphs() const;
    };
}
