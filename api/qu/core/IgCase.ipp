////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/core/IgCase.hpp>

#include <QByteArray>
#include <QString>

namespace qu {
    bool    IgCase::operator()(const QString&a, const QString&b) const
    {
        return QString::compare(a,b,Qt::CaseInsensitive) < 0;
    }


    bool    IgCase::operator()(const QByteArray&a, const QByteArray&b) const
    {
        return a.compare(b,Qt::CaseInsensitive) < 0;
    }

}

