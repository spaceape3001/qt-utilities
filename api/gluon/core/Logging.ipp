////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Logging.hpp"

#include <QByteArray>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QUrl>

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QByteArray&v)
{
    return cs << v.constData();
}


log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QDate&v)
{
    return cs << v.toString(Qt::ISODate);
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QDateTime&v)
{
    return cs << v.toString(Qt::ISODate);
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QDir& v)
{
    return cs << v.absolutePath();
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QString&v)
{
    return cs << v.toStdString();
}


log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QUrl&v)
{
    return cs << v.toString();
}
