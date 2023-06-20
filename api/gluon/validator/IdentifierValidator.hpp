////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QValidator>

namespace yq::gluon {
    class IdentifierValidator : public QValidator {
        Q_OBJECT
    public:
        IdentifierValidator(QObject*parent=nullptr);
        ~IdentifierValidator();
        
        void                fixup(QString&input) const override;
        QValidator::State   validate(QString& input, int& pos) const override;
    };
}
