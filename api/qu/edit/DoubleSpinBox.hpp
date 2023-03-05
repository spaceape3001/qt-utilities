////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QDoubleSpinBox>
#include <qu/undo/UndoBase.hpp>

namespace qu {
    class DoubleSpinBox : public QDoubleSpinBox, public UndoBase {
        Q_OBJECT
    public:
        DoubleSpinBox(QWidget*parent=nullptr);
        ~DoubleSpinBox();
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    public slots:   
        virtual void    reset();
    };
}
