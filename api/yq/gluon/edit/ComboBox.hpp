////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/undo/UndoBase.hpp>
#include <QComboBox>

namespace yq::gluon {

    /*! \brief Combo Box with undo API
    */
    class ComboBox : public QComboBox, public UndoBase {
        Q_OBJECT
    public:
    
        //! Constructor
        ComboBox(QWidget* parent=nullptr);
        
        //! Destructor
        virtual ~ComboBox();
        
    public slots:
        virtual void    reset();
    };
}
