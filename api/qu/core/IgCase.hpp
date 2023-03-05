////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <basic/IgCase.hpp>

class QString;
class QByteArray;

namespace qu {
    struct IgCase : public yq::IgCase {
        using yq::IgCase::operator();
        bool    operator()(const QString&, const QString&) const;
        bool    operator()(const QByteArray&, const QByteArray&) const;
    };
    
}
