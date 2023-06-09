////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QDoubleSpinBox>
#include <gluon/undo/UndoBase.hpp>

namespace yq::gluon {
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
