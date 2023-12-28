////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/IgCase.hpp>

class QString;
class QByteArray;

namespace yq::gluon {

    //! String Comparison to ignore case
    //!
    //! Standard empty class that's comparing strings & making them 
    //! Case-insensitive
    struct IgCaseQ : public IgCase {
    
        //! Allow for the normal comparisons
        using IgCase::operator();
        
        //! QString comparison
        bool  operator()(const QString&, const QString&) const;

        //! QByteArray comparison
        bool  operator()(const QByteArray&, const QByteArray&) const;
    };
    
}
