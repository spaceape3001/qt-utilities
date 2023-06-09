////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/ThreadId.hpp>
#include <gluon/core/Utilities.hpp>

#include <QFileInfo>
#include <QIcon>

namespace yq::gluon {

    Compare compare_igCase(const QString& a, const QString& b)
    {
        int r   = QString::compare(a,b,Qt::CaseInsensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
    }

    Compare compare_igCase(const QByteArray& a, const QByteArray& b)
    {
        int r	= a.compare(b,Qt::CaseInsensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
    }

    QIcon                fetchIcon(const QString&file)
    {
        if(is_main_thread()){
            static const char *sizes[] = { "16", "016", "24", "024", "32", "032", "48",
                                           "048", "64", "064", "96", "096", "128", 
                                           "144", "192", "256" };
            QIcon   res;
            for(const char* z : sizes){
                QString name    = file.arg(z);
                if(QFileInfo(name).exists())
                    res.addFile(name);
            }
            
            return res;
        } else
            return QIcon();
    }


    bool    is_similar(const QString&a, const QString&b)
    {
        return QString::compare(a,b,Qt::CaseInsensitive) == 0;
    }
    
    bool    is_similar(const QByteArray&a, const QByteArray&b)
    {
        return a.compare(b,Qt::CaseInsensitive) == 0;
    }
    
    QString qString(std::string_view v)
    {
        if(v.empty())
            return QString();
        return QString::fromUtf8(v.data(), v.size());
    }
}
