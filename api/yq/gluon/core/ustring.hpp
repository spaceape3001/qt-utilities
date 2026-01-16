////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QString>
#include <string>
#include <string_view>

namespace yq {
    inline QString      qString(std::string_view sv)
    {
        if(sv.empty())
            return QString();
        return QString::fromUtf8(sv.data(), sv.size());
    }

    inline std::string  sString(const QString& str)
    {
        return str.toStdString();
    }
}
