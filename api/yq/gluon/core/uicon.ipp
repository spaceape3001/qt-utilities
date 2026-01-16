////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "uicon.hpp"

#include <yq/core/ThreadId.hpp>

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
