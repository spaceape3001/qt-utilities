////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QValidator>

namespace yq::gluon {
    /*! \brief Validator for Xml tags
    
        This validates the input to make sure it matches valid HTML tags
    */
    class XmlIdentifierValidator : public QValidator {
        Q_OBJECT
    public:
    
        //! Constructor
        XmlIdentifierValidator(QObject*parent=nullptr);
        
        //! Destructor
        ~XmlIdentifierValidator();
        
        //! Static is valid checker
        static bool     isValid(const QString&, int* pos=nullptr);
        
        //! Fixes up the input
        void                fixup(QString&input) const override;
        
        //! Validates the input
        QValidator::State   validate(QString& input, int& pos) const override;
    };
}
