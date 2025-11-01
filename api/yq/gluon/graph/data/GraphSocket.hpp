////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/graph/preamble.hpp>
#include <QStringList>

namespace yq::gluon {
    class GraphSocket : public QObject {
        Q_OBJECT
    public:
        GraphSocket(QObject*parent=nullptr);
        GraphSocket(const g::Socket&, QObject*parent=nullptr);
        ~GraphSocket();
        
        bool operator==(const GraphSocket&) const;
        
        g::Socket       get() const;
        void            saveTo(g::Socket&) const;
        
        const QString&  node() const { return m_node; }
        const QString&  pin() const { return m_pin; }
        const QString&  sub() const { return m_sub; }
        const QStringList&  nodes() const { return m_nodes; }
        
    public slots:
        void        setNode(const QString&);
        void        setPin(const QString&);
        void        setSub(const QString&);
        void        setNodes(const QStringList&);
        
    signals:
        void        nodeChanged(const QString&);
        void        pinChanged(const QString&);
        void        subChanged(const QString&);
        void        nodesChanged(const QStringList&);
        
    private:
        QString     m_node;
        QString     m_pin;
        QString     m_sub;
        QStringList m_nodes;
    };
}
