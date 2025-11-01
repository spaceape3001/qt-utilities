////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graph/data/GraphBase.hpp>

namespace yq::gluon {
    class GraphEdge : public GraphBase {
        Q_OBJECT
    public:
        GraphEdge(QObject* parent=nullptr);
        GraphEdge(const g::Edge&, QObject* parent=nullptr);
        ~GraphEdge();
        
        bool    operator==(const GraphEdge&) const;
        
        g::Edge get() const;
        void    saveTo(g::Edge&) const;
        
        GraphSocket*    source() const { return m_source; }
        GraphSocket*    target() const { return m_target; }
        const QStringList&  datas() const { return m_datas; }
        
    public slots:
        void        setDatas(const QStringList&);
    
    signals:
        void        datasChanged(const QStringList&);
        
    private:
        GraphSocket*    m_source    = nullptr;
        GraphSocket*    m_target    = nullptr;
        QStringList     m_datas;
    };
}
