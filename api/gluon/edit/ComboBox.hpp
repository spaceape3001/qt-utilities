////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QComboBox>

namespace yq::gluon {

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
