////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphBase.hpp"
#include "GraphProperty.hpp"
#include <gluon/preamble.hpp>

namespace yq::gluon {
    GraphProperty::GraphProperty(GraphBase*parent) : GraphName(parent)
    {
    }
    
    GraphProperty::GraphProperty(const g::Property&v, GraphBase*parent) : GraphName(v, parent)
    {
        m_value = qVariant(v.value);
        m_count = v.count;
    }
    
    GraphProperty::~GraphProperty()
    {
    }

    bool    GraphProperty::operator==(const GraphProperty&v) const
    {
        return GraphName::operator==(v) &&
            ( m_value == v.m_value ) &&
            ( m_count == v.m_count )
        ;
    }
    
    g::Property GraphProperty::get() const
    {
        g::Property ret;
        saveTo(ret);
        return ret;
    }
    
    void        GraphProperty::saveTo(g::Property&v) const
    {
        GraphName::saveTo(v);
        v.value = yAny(m_value);
        v.count = m_count;
    }

    void    GraphProperty::setCountMin(unsigned v)
    {
        if(v != m_count.min){
            m_count.min = v;
            emit countMinChanged(v);
        }
    }
    
    void    GraphProperty::setCountMax(unsigned v)
    {
        if(v != m_count.max){
            m_count.max = v;
            emit countMaxChanged(v);
        }
    }
    
    void    GraphProperty::setCountDef(unsigned v)
    {
        if(v != m_count.def){
            m_count.def = v;
            emit countDefChanged(v);
        }
    }
    
    void    GraphProperty::setMultiFlag(bool f)
    {
        setOption(g::Option::MULTI, f);
    }
    
    void    GraphProperty::setValue(const QVariant&v)
    {
        if(m_value != v){
            m_value = v;
            emit valueChanged(v);
        }
    }
}

#include "moc_GraphProperty.cpp"
