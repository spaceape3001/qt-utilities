////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/Logging.hpp>

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
class QString;
class QUrl;

log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QByteArray&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDate&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDateTime&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QDir&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QString&);
log4cpp::CategoryStream& operator<<(log4cpp::CategoryStream&, const QUrl&);
