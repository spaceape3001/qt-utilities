////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <0/basic/preamble.hpp>
#include <QStringList>

class QMetaType;
class QVariant;

namespace yq {
    class Any;
}

namespace yq::gluon {
    typedef QVariant (*AnyToQVariantFN)(const Any&);
    typedef Any      (*QVariantToAnyFN)(const QVariant&);

    QString                 qString(std::string_view sv);
    QString                 qFilePath(const std::filesystem::path&);

    QVariant                qVariant(const Any& v);
    QVariant                qVariant(std::string_view sv);
    QStringList             qStringList(std::span<const std::string> sp);
    QStringList             qStringList(std::span<const std::string_view>sp);
    
    std::string             yString(const QString&s);
    Any                     yAny(const QVariant&v);
    string_vector_t         yStringVector(const QStringList&sl);
    
    std::filesystem::path   yFilePath(const QString&);
}
