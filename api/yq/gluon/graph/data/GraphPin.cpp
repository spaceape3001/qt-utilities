////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphPin.hpp"

namespace yq::gluon {
    GraphPin::GraphPin(QObject*parent) : GraphBase(parent)
    {
    }
    
    GraphPin::GraphPin(const g::Pin& v, QObject*parent) : GraphBase(v, parent)
    {
        m_flow  = v.flow;
        m_count = v.count;
    }
    
    GraphPin::~GraphPin()
    {
    }

    bool    GraphPin::operator==(const GraphPin&v) const
    {
        return 
            GraphBase::operator==(v) &&
            (m_flow == v.m_flow) &&
            (m_count == v.m_count);
    }

    g::Pin  GraphPin::get() const
    {
        g::Pin  ret;
        saveTo(ret);
        return ret;
    }
    
    void    GraphPin::saveTo(g::Pin& v) const
    {
        GraphBase::saveTo(v);
        v.flow      = m_flow;
        v.count     = m_count;
    }


    void    GraphPin::setCountMin(unsigned v)
    {
        if(v != m_count.min){
            m_count.min = v;
            emit countMinChanged(v);
        }
    }
    
    void    GraphPin::setCountMax(unsigned v)
    {
        if(v != m_count.max){
            m_count.max = v;
            emit countMaxChanged(v);
        }
    }
    
    void    GraphPin::setCountDef(unsigned v)
    {
        if(v != m_count.def){
            m_count.def = v;
            emit countDefChanged(v);
        }
    }
    
    void    GraphPin::setFlow(g::Flow v)
    {
        if(v != m_flow){
            m_flow  = v;
            emit flowChanged(v);
        }
    }

    void    GraphPin::setMultiFlag(bool f)
    {
        setOption(g::Option::MULTI, f);
    }
    
}

#include "moc_GraphPin.cpp"
