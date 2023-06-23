////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Int64SignalMapper.hpp"

namespace yq::gluon {
    Int64SignalMapper::Int64SignalMapper(QObject* parent) 
        : QObject(parent)
    {
    }

    Int64SignalMapper::~Int64SignalMapper()
    {
    }

    void        Int64SignalMapper::setMapping(QObject*sender, int64_t i)
    {
        m_mapping[sender]  = i;
        connect(sender, SIGNAL(destroyed()), this, SLOT(remove()));
    }

    void        Int64SignalMapper::removeMappings(QObject*sender)
    {
        m_mapping.erase(sender);
        if(sender)
            sender->disconnect(this);
    }

    void        Int64SignalMapper::map()
    {
        QObject*    s   = sender();
        auto i = m_mapping.find(s);
        if(i != m_mapping.end())
            emit mapped(i->second);
    }

    void        Int64SignalMapper::remove()
    {
        QObject*    s   = sender();
        m_mapping.erase(s);
    }
}

#include "moc_Int64SignalMapper.cpp"
