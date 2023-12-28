////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/ThreadId.hpp>
#include <gluon/core/Utilities.hpp>
#include <gluon/core/Logging.hpp>

#include <QDate>
#include <QDateTime>
#include <QDirIterator>
#include <QFileInfo>
#include <QIcon>
#include <QObject>
#include <QTime>
#include <QUuid>

namespace yq::gluon {

    Compare     compare(const QByteArray&a, const QByteArray&b)
    {
        int r	= a.compare(b,Qt::CaseSensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
    }
    
    Compare     compare(const QString&a, const QString&b)
    {
        int r   = QString::compare(a,b,Qt::CaseInsensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
    }
    
    static Compare  finalCompare(const QVariant& a, const QVariant& b, bool igCase)
    {
        if(a.userType() == b.userType()){
            switch(a.userType()){
            case QMetaType::QString:
                break;
            case QMetaType::Bool:
            case QMetaType::LongLong:
            case QMetaType::Long:
            case QMetaType::Char:
            case QMetaType::Int:
            case QMetaType::Short:
                return compare(a.toLongLong(), b.toLongLong());
            case QMetaType::ULongLong:
            case QMetaType::ULong:
            case QMetaType::UChar:
            case QMetaType::UInt:
            case QMetaType::UShort:
                return compare(a.toULongLong(), b.toULongLong());
            case QMetaType::Float:
            case QMetaType::Double:
                return compare(a.toDouble(), b.toDouble());
            case QMetaType::QDate:
                return compare(a.toDate(), b.toDate());
            case QMetaType::QDateTime:
                return compare(a.toDateTime(), b.toDateTime());
            case QMetaType::QTime:
                return compare(a.toTime(), b.toTime());
            case QMetaType::QUuid:
                return compare(a.value<QUuid>(), b.value<QUuid>());
            default:
                break;
            }
        }
        
        if(igCase){
            return compare_igCase(a.toString(), b.toString());
        } else  {
            return compare(a.toString(), b.toString());
        }
    }

    Compare     compare(const QVariant&a, const QVariant&b)
    {
        if(a.metaType() == b.metaType())
            return finalCompare(a,b,false);

        // alright, not equal....
        if(a.canConvert(b.metaType())){
            if(a.metaType().sizeOf() > b.metaType().sizeOf()){
                QVariant ta = a;
                ta.convert(b.metaType());
                return finalCompare(ta, b, false);
            } else {
                QVariant tb = b;
                tb.convert(a.metaType());
                return finalCompare(a, tb, false);
            }
        }

        return finalCompare(a,b, false);
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

    Compare compare_igCase(const QString& a, const QString& b)
    {
        int r   = QString::compare(a,b,Qt::CaseInsensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
    }


    Compare     compare_igCase(const QVariant&a, const QVariant&b)
    {
        if(a.metaType() == b.metaType())
            return finalCompare(a,b, true);

        // alright, not equal....
        if(a.canConvert(b.metaType())){
            if(a.metaType().sizeOf() > b.metaType().sizeOf()){
                QVariant ta = a;
                ta.convert(b.metaType());
                return finalCompare(ta, b, true);
            } else {
                QVariant tb = b;
                tb.convert(a.metaType());
                return finalCompare(a, tb, true);
            }
        }

        return finalCompare(a,b,true);
    }


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

    std::vector<const QObject*>   qobjectLineage(const QObject* obj, bool fIncSelf)
    {
        std::vector<const QObject*>   ret;
        if(obj){
            if(fIncSelf)
                ret.push_back(obj);
            for(QObject*p   = obj->parent(); p; p=p->parent())
                ret.push_back(p);
        }
        return std::vector<const QObject*>(ret.rbegin(), ret.rend());
    }

    void    logAllResources()
    {
        logAllResources(qtInfo);
    }
    
    void    logAllResources(log4cpp::CategoryStream&&log)
    {
        log << "All Registered Qt Resources:\n";
        size_t n    = 0;
        QDirIterator it(":", QDirIterator::Subdirectories);
        while (it.hasNext()){
            log << "+ " << it.next() << '\n';
            ++n;
        }
        log << "Found " << n << " items.";
    }
}
