////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/core/Logging.hpp>

#include <QByteArray>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QLayout>
#include <QLayoutItem>
#include <QMetaObject>
#include <QObject>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QSize>
#include <QUrl>
#include <QWidget>

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

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QPoint&v)
{
    return cs << "{" << v.x() << "," << v.y() << "}";
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&cs, const QPointF&v)
{
    return cs << "{" << v.x() << "," << v.y() << "}";
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

const char*     className(const QObject* obj)
{
    if(!obj)
        return "null object";
    return obj -> metaObject() -> className();
}

const char*     className(const QLayoutItem* lay)
{
    if(!lay)
        return "null layout item";
    if(const QWidget* w = lay->widget())
        return w->metaObject()->className();
    if(const QLayout* l = const_cast<QLayoutItem*>(lay)->layout())
        return l->metaObject()->className();
    return "empty layout item";
}

