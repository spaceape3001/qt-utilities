////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/undo/UndoBase.hpp>
#include <QDateEdit>

namespace yq::gluon {

    /*! \brief Date Edit with UNDO
    
        \note This is a stub... the actual undo will come later
    */
    class DateEdit : public QDateEdit, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        DateEdit(QWidget* parent = nullptr);
        
        //! Destructor
        ~DateEdit();
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented
    };
}
