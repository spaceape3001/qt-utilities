////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "UInt64SignalMapper.hpp"

namespace yq::gluon {
    UInt64SignalMapper::UInt64SignalMapper(QObject* parent) 
        : QObject(parent)
    {
    }

    UInt64SignalMapper::~UInt64SignalMapper()
    {
    }

    void        UInt64SignalMapper::setMapping(QObject*sender, uint64_t i)
    {
        m_mapping[sender]  = i;
        connect(sender, SIGNAL(destroyed()), this, SLOT(remove()));
    }

    void        UInt64SignalMapper::removeMappings(QObject*sender)
    {
        m_mapping.erase(sender);
        if(sender)
            sender->disconnect(this);
    }

    void        UInt64SignalMapper::map()
    {
        QObject*    s   = sender();
        auto i = m_mapping.find(s);
        if(i != m_mapping.end())
            emit mapped(i->second);
    }

    void        UInt64SignalMapper::remove()
    {
        QObject*    s   = sender();
        m_mapping.erase(s);
    }
}

#include "moc_UInt64SignalMapper.cpp"
