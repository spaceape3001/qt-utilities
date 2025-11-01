////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphEdge.hpp"
#include "GraphSocket.hpp"
#include <gluon/preamble.hpp>
#include <gluon/core/Utilities.hpp>

namespace yq::gluon {
    GraphEdge::GraphEdge(QObject* parent) : GraphBase(parent)
    {
        m_source    = new GraphSocket(this);
        m_target    = new GraphSocket(this);
    }
    
    GraphEdge::GraphEdge(const g::Edge&v, QObject* parent) : GraphBase(v, parent)
    {
        m_datas     = qStringList(v.datas);
        m_source    = new GraphSocket(v.source, this);
        m_target    = new GraphSocket(v.target, this);
    }
    
    GraphEdge::~GraphEdge()
    {
    }
    
    bool    GraphEdge::operator==(const GraphEdge&v) const
    {
        return GraphBase::operator==(v) && (*m_source == *v.m_source) && (*m_target == *v.m_target);
    }
    
    
    g::Edge GraphEdge::get() const
    {
        g::Edge ret;
        saveTo(ret);
        return ret;
    }
    
    void    GraphEdge::saveTo(g::Edge&v) const
    {
        GraphBase::saveTo(v);
        v.datas = yStringVector(m_datas);
        m_source->saveTo(v.source);
        m_target->saveTo(v.target);
    }

    void        GraphEdge::setDatas(const QStringList& v)
    {
        if(v != m_datas){
            m_datas = v;
            datasChanged(v);
        }
    }
}

#include "moc_GraphEdge.cpp"
