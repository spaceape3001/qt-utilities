////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/IgCase.hpp>

class QString;
class QByteArray;

namespace yq::gluon {
    struct IgCaseQ : public IgCase {
        using IgCase::operator();
        bool  operator()(const QString&, const QString&) const;
        bool  operator()(const QByteArray&, const QByteArray&) const;
    };
    
}
