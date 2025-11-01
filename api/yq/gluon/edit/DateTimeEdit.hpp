////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/undo/UndoBase.hpp>
#include <QDateTimeEdit>

namespace yq::gluon {

    /*! \brief Date Time Edit with UNDO
    
        \note This is a stub... the actual undo will come later
    */
    class DateTimeEdit : public QDateTimeEdit, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        DateTimeEdit(QWidget* parent = nullptr);
        
        //! Destructor
        ~DateTimeEdit();
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
    };
}
