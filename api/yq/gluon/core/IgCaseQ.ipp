////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/core/IgCaseQ.hpp>

#include <QByteArray>
#include <QString>

namespace yq {
    bool    IgCaseQ::operator()(const QString&a, const QString&b) const
    {
        return QString::compare(a,b,Qt::CaseInsensitive) < 0;
    }


    bool    IgCaseQ::operator()(const QByteArray&a, const QByteArray&b) const
    {
        return a.compare(b,Qt::CaseInsensitive) < 0;
    }

}

