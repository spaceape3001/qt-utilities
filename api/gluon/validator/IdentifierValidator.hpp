////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QValidator>

namespace yq::gluon {

    /*! \brief Validator for Identifiers
    
        A valid identifier is one that starts with a letter, optionally followed
        by one or more underscores, letters, and/or numbers
    */
    class IdentifierValidator : public QValidator {
        Q_OBJECT
    public:
        //! Constructor
        IdentifierValidator(QObject*parent=nullptr);
        
        //! Destructor
        ~IdentifierValidator();
        
        //! Fixes the input (ie delete offenders)
        void                fixup(QString&input) const override;
        
        //! Validation method
        QValidator::State   validate(QString& input, int& pos) const override;
    };
}
