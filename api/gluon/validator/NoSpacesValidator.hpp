////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QValidator>

namespace yq::gluon {
    /*! \brief Validator that disallows spaces
    
        Simple validator that rejects all whitespace
    */
    class NoSpacesValidator : public QValidator {
        Q_OBJECT
    public:    
    
        //! Constructor
        NoSpacesValidator(QObject*parent=nullptr);
        
        //! Destructor
        ~NoSpacesValidator();

        //! Fixes the string (ie deletes the spaces)
        void                fixup(QString&input) const override;
        
        //! Validates the string
        QValidator::State   validate(QString& input, int& pos) const override;
    };
}
