////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphSocket.hpp"
#include <gluon/preamble.hpp>
#include <gluon/core/Utilities.hpp>

namespace yq::gluon {
    GraphSocket::GraphSocket(QObject*parent) : QObject(parent)
    {
    }
    
    GraphSocket::GraphSocket(const g::Socket&v, QObject*parent) : QObject(parent)
    {
        m_node          = qString(v.node);
        m_pin           = qString(v.pin);
        m_sub           = qString(v.sub);
        m_nodes         = qStringList(v.nodes);
    }
    
    GraphSocket::~GraphSocket()
    {
    }
    
    bool GraphSocket::operator==(const GraphSocket&v) const
    {
        return (m_node == v.m_node) && (m_pin == v.m_pin) && (m_sub == v.m_sub) && (m_nodes == v.m_nodes);
    }
    
    
    g::Socket       GraphSocket::get() const
    {
        g::Socket   ret;
        saveTo(ret);
        return ret;
    }
    
    void            GraphSocket::saveTo(g::Socket&v) const
    {
        v.node      = m_node.toStdString();
        v.pin       = m_pin.toStdString();
        v.sub       = m_sub.toStdString();
        v.nodes     = yStringVector(m_nodes);
    }
    
    void        GraphSocket::setNode(const QString&v)
    {
        if(v != m_node){
            m_node  = v;
            emit nodeChanged(v);
        }
    }
    
    void        GraphSocket::setPin(const QString&v)
    {
        if(v != m_pin){
            m_pin   = v;
            emit pinChanged(v);
        }
    }
    
    void        GraphSocket::setSub(const QString&v)
    {
        if(v != m_sub){
            m_sub   = v;
            emit subChanged(v);
        }
    }
    
    void        GraphSocket::setNodes(const QStringList&v)
    {
        if(v != m_nodes){
            m_nodes = v;
            emit nodesChanged(v);
        }
    }
}

#include "moc_GraphSocket.cpp"
