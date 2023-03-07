////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/core/Utilities.hpp>

namespace qu {

    yq::Compare compare_igCase(const QString& a, const QString& b)
    {
        int r   = QString::compare(a,b,Qt::CaseInsensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
    }

    yq::Compare compare_igCase(const QByteArray& a, const QByteArray& b)
    {
        int r	= a.compare(b,Qt::CaseInsensitive);
        if(r<0)
            return yq::Compare::LESSER;
        if(r>0)
            return yq::Compare::GREATER;
        return yq::Compare::EQUAL;
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
