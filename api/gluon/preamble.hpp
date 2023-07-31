////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/preamble.hpp>

class QString;
class QVariant;

namespace yq {
    class Any;
}

namespace yq::gluon {
    struct IgCaseQ;
    
    using QStringMap            = Map<QString,QString,IgCaseQ>;
    using QStringSet            = Set<QString,IgCaseQ>;

    QString     qString(std::string_view);
    std::string yString(const QString&);
    
    QVariant    qVariant(const Any&);
    QVariant    qVariant(std::string_view);
    Any         yAny(const QVariant&);
}

