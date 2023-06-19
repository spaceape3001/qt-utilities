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
#include <QObject>
#include <QMetaObject>

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

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const AsList<std::vector<const QObject*>>& list)
{
    cs << '\n';
    for(const QObject* obj : list.value)
        cs << (const void*) obj << ": " << obj->metaObject()->className() << '\n';
    return cs;
}

