////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "Application.hpp"
#include <gluon/core/Logging.hpp>

namespace yq::gluon {
    namespace {
        static void         log_qt(log4cpp::CategoryStream&& cs, const QMessageLogContext& context, const QString& msg)
        {
            QByteArray  utf8    = msg.toUtf8();
            const char* file    = context.file ? context.file : "??";
            const char* fn      = context.function ? context.function : "??";
            cs << utf8.constData() << " (" << file << ":" << context.line << ", " << fn << ")";
        }

        static void        log4cpp_qtMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
        {
            static log4cpp::Category&   logger  = log4cpp::Category::getInstance("qt");
            switch(type){
            case QtDebugMsg:
                log_qt(logger.debugStream(), context, msg);
                break;
            case QtInfoMsg:
                log_qt(logger.infoStream(), context, msg);
                break;
            case QtWarningMsg:
                log_qt(logger.warnStream(), context, msg);
                break;
            case QtCriticalMsg:
                log_qt(logger.critStream(), context, msg);
                break;
            case QtFatalMsg:
                log_qt(logger.fatalStream(), context, msg);
                break;
            }
        }
    }


    Application*    Application::s_app  = nullptr;

    Application*     Application::app()
    {
        return s_app;
    }

    Application::Application(int&argc, char**argv) : QApplication(argc, argv), BasicApp(argc, argv)
    {
        if(!s_app)
            s_app   = this;
        qInstallMessageHandler(log4cpp_qtMessageHandler);
    }
    
    Application::~Application()
    {
        if(s_app == this)
            s_app   = nullptr;
    }
}

#include "moc_Application.cpp"
