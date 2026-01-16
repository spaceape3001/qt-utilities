////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Compare.hpp>

class QByteArray;
class QVariant;
class QString;

namespace yq {
    Compare         compare(const QByteArray&, const QByteArray&);
    Compare         compare(const QString&, const QString&);
    Compare         compare(const QVariant&, const QVariant&);

    Compare         compare_igCase(const QByteArray& a, const QByteArray& b);
    Compare         compare_igCase(const QString& a, const QString& b);
    
    Compare         compare_igCase(const QVariant&, const QVariant&);
}
