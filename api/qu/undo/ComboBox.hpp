////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/undo/UndoBase.hpp>
#include <QComboBox>

namespace qu {

    /*! \brief Combo Box with undo API
    */
    class ComboBox : public QComboBox, public UndoBase {
        Q_OBJECT
    public:

        ComboBox(QWidget* parent=nullptr);
        virtual ~ComboBox();
        
    public slots:
        virtual void    reset();
    };
}
