////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ucompare.hpp"
#include <QByteArray>
#include <QDate>
#include <QDateTime>
#include <QString>
#include <QTime>
#include <QUuid>
#include <QUrl>
#include <QVariant>

namespace yq {

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
            case QMetaType::QUrl:
                return compare(a.toUrl(), b.toUrl());
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
}
