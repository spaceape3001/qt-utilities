////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "umatch.hpp"
#include <QString>
#include <QByteArray>

namespace yq {
    bool    is_similar(const QString&a, const QString&b)
    {
        return QString::compare(a,b,Qt::CaseInsensitive) == 0;
    }
    
    bool    is_similar(const QByteArray&a, const QByteArray&b)
    {
        return a.compare(b,Qt::CaseInsensitive) == 0;
    }
}
