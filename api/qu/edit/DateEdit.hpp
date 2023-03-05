////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/undo/UndoBase.hpp>
#include <QDateEdit>

namespace qu {

    /*! \brief Date Edit with UNDO
    
        \note This is a stub... the actual undo will come later
    */
    class DateEdit : public QDateEdit, public UndoBase {
        Q_OBJECT
    public:
        DateEdit(QWidget* parent = nullptr);
        ~DateEdit();
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
    };
}
