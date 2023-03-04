////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/undo/UndoBase.hpp>
#include <QCheckBox>

namespace qu {

    /*! \brief Undoable checkbox with boolean value
    */
    class CheckBox : public QCheckBox, public UndoBase {
        Q_OBJECT
    public:
        CheckBox(QWidget* parent=nullptr);
        CheckBox(const QString& text, QWidget* parent=nullptr);
        virtual ~CheckBox();
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

        bool    isChecked() const;
        void    setChecked(bool);
    };

}
