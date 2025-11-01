////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QCheckBox>

namespace yq::gluon {

    /*! \brief Undoable checkbox with boolean value
    
        \note Currently undo is a stub
    */
    class CheckBox : public QCheckBox, public UndoBase {
        Q_OBJECT
    public:
        
        //! Constructor
        CheckBox(QWidget* parent=nullptr);
        
        //! Constructor with label
        CheckBox(const QString& text, QWidget* parent=nullptr);
        
        //! Destruct
        virtual ~CheckBox();
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

        //! True if we're checked
        bool    isChecked() const;
        
        //! Sets the checked state (on/off)
        void    setChecked(bool);
    };

}
