////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "uicon.hpp"

#include <yq/core/ThreadId.hpp>
#include <yq/gluon/logging.hpp>
#include <yq/gluon/core/ustring.hpp>
#include <yq/gluon/core/Logging.hpp>
#include <yq/net/Url.hpp>
#include <yq/resource/Resource.hpp>
#include <yq/text/match.hpp>

#include <QFile>
#include <QIcon>
#include <QString>

namespace yq::gluon {
    QIcon                fetchIcon(const QString&file)
    {
        if(is_main_thread()){
            if(QFile::exists(file)) // straight up... return if fine
                return QIcon(file);
        
            static const char *sizes[] = { "16", "016", "24", "024", "32", "032", "48",
                                           "048", "64", "064", "96", "096", "128", 
                                           "144", "192", "256" };
            QIcon   res;
            for(const char* z : sizes){
                QString name    = file.arg(z);
                if(QFile::exists(name))
                    res.addFile(name);
            }
            
            return res;
        } else
            return QIcon();
    }
}

namespace yq {
    QIcon       qIcon(std::string_view sv)
    {
        if(!is_main_thread()){
            gluonOnceWarning << "qIcon(" << sv << "): not the main thread";
            return QIcon();
        }
            
        Url u2  = Resource::resolve(sv);
        if(!is_similar(u2.scheme, "file")){
            gluonFirstWarning(u2) << "qIcon(" << sv << "): not a local file";
            return QIcon();
        }
        if(!u2.fragment.empty()){
            gluonFirstWarning(u2) << "qIcon(" << sv << "): has a fragment";
            return QIcon();
        }
        if(!u2.query.empty()){
            gluonFirstWarning(u2) << "qIcon(" << sv << "): has a query";
            return QIcon();
        }
        if(!u2.host.empty()){
            gluonFirstWarning(u2) << "qIcon(" << sv << "): has a host";
            return QIcon();
        }
        
        return QIcon(qString(u2.path));
    }
}
