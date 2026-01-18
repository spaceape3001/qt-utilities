////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Logging.hpp>

#define qtAlert             yAlert("qt")
#define qtCritical          yCritical("qt")
#define qtDebug             yDebug("qt")
#define qtError             yError("qt")
#define qtEmergency         yEmergency("qt")
#define qtFatal             yFatal("qt")
#define qtInfo              yInfo("qt")
#define qtNotice            yNotice("qt")
#define qtWarning           yWarning("qt")

class QByteArray;
class QDate;
class QDateTime;
class QDir;
class QLayoutItem;
class QRect;
class QRectF;
class QSize;
class QString;
class QObject;
class QUrl;
class QPoint;
class QPointF;

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QByteArray&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDate&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDateTime&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDir&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QPoint&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QPointF&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QRect&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QRectF&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QSize&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QString&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QUrl&);

const char*     className(const QObject*);
const char*     className(const QLayoutItem*);

template <typename T>
struct AsList {
    T     value;
};

template <typename T>
AsList<T>   as_list(const T& obj)
{
    return AsList<T>(obj);
}

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const AsList<std::vector<const QObject*>>&);
