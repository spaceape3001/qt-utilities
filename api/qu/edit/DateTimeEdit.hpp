////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/undo/UndoBase.hpp>
#include <QDateTimeEdit>

namespace qu {

    /*! \brief Date Time Edit with UNDO
    
        \note This is a stub... the actual undo will come later
    */
    class DateTimeEdit : public QDateTimeEdit, public UndoBase {
        Q_OBJECT
    public:
        DateTimeEdit(QWidget* parent = nullptr);
        ~DateTimeEdit();
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
    };
}
