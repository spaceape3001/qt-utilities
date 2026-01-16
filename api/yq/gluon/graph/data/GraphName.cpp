////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/graph/preamble.hpp>
#include <yq/gluon/core/ustring.hpp>
#include "GraphName.hpp"

namespace yq::gluon {
    GraphName::GraphName(QObject* parent) : QObject(parent)
    {
    }
    
    GraphName::GraphName(const g::TND&v, QObject* parent) : GraphName(parent)
    {
        m_name          = qString(v.name);
        m_type          = qString(v.type);
        m_description   = qString(v.description);
        m_notes         = qString(v.notes);
        m_options       = v.options;
    }
    
    GraphName::~GraphName()
    {
    }

    bool        GraphName::operator==(const GraphName&v) const
    {
        return 
            (m_name == v.m_name) &&
            (m_type == v.m_type) &&
            (m_description == v.m_description) &&
            (m_notes == v.m_notes) &&
            (m_options == v.m_options)
        ;
    }
    
    g::TND      GraphName::get() const
    {
        g::TND ret;
        saveTo(ret);
        return ret;
    }
    
    void    GraphName::saveTo(g::TND&v) const
    {
        v.name          = sString(m_name);
        v.type          = sString(m_type);
        v.description   = sString(m_description);
        v.notes         = sString(m_notes);
        v.options       = m_options;
    }

    void    GraphName::setDescription(const QString&v)
    {
        if(v != m_description){
            m_description       = v;
            emit descriptionChanged(v);
        }
    }

    void    GraphName::setInfoFlag(bool f)
    {
        if(f != isInfo()){
            if(f)
                m_options.set(g::Option::INFO);
            else
                m_options.clear(g::Option::INFO);
            emit infoFlagChanged(f);
        }
    }
    
    void    GraphName::setName(const QString&v)
    {
        if(v != m_name){
            m_name  = v;
            emit nameChanged(v);
        }
    }
    
    void    GraphName::setNotes(const QString&v)
    {
        if(v != m_notes){
            m_notes = v;
            emit notesChanged(v);
        }
    }

    void    GraphName::setOption(g::Option opt, bool v)
    {
        if(m_options[opt] != v){
            if(v)
                m_options.set(opt);
            else
                m_options.clear(opt);
                
            switch(opt){
            case g::Option::INFO:
                emit infoFlagChanged(v);
                break;
            case g::Option::PINS:
                emit pinsFlagChanged(v);
                break;
            case g::Option::MULTI:
                emit multiFlagChanged(v);
                break;
            default:
                break;
            }
        }
    }
    
    void    GraphName::setOptions(Flag<g::Option>v)
    {
        if(v != m_options){
            Flag<g::Option> chg     = m_options ^ v;
            m_options   = v;
            if(chg[g::Option::INFO])
                emit infoFlagChanged(v[g::Option::INFO]);
            if(chg[g::Option::PINS])
                emit pinsFlagChanged(v[g::Option::PINS]);
            if(chg[g::Option::MULTI])
                emit multiFlagChanged(v[g::Option::MULTI]);
        }
    }
    
    void    GraphName::setType(const QString&v)
    {
        if(v != m_type){
            m_type  = v;
            emit typeChanged(v);
        }
    }
}

#include "moc_GraphName.cpp"
