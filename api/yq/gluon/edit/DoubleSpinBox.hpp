////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QDoubleSpinBox>
#include <yq/gluon/undo/UndoBase.hpp>

namespace yq::gluon {

    /*! \brief Double Spin Box with Undo Capability
    
        (well, eventually, not right now, the undo is actually TODO)
    */
    class DoubleSpinBox : public QDoubleSpinBox, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        DoubleSpinBox(QWidget*parent=nullptr);
        
        //! Destructor
        ~DoubleSpinBox();
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    public slots:   
        //! Reset to default
        virtual void    reset();
    };
}
