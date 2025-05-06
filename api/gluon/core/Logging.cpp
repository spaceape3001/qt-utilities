////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/core/Logging.hpp>

#include <QByteArray>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QMetaObject>
#include <QObject>
#include <QRect>
#include <QSize>
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

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QRect&v)
{
    return cs << "{" << v.width() << " x " << v.height() << " @ " << v.x() << ", " << v.y() << "}";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QSize& v)
{
    return cs << "{" << v.width() << " x " << v.height() << "}";
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

