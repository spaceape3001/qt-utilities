////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/core/RefQ.hpp>
#include <QObject>

namespace qu {

    RefQ::RefQ()
    {
        m_count     = 0;
    }

    RefQ::RefQ(const RefQ&)
    {
        m_count     = 0;
    }

    void	RefQ::incRef() const
    {
        ++m_count;
    }

    void	RefQ::decRef() const
    {
        if(!--m_count) {
            const QObject*    obj   = dynamic_cast<const QObject*>(this);
            if(obj){
                const_cast<QObject*>(obj) -> deleteLater();
            } else {
                delete this;
            }
        }
    }
}
