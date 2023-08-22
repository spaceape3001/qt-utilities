////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/edit/ComboBox.hpp>

class QColor;

namespace yq::gluon {

    //! Combo box of colors
    class ColorComboBox : public ComboBox {
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor USER true)
    public:
    
        //! Constructor
        ColorComboBox(QWidget* parent=nullptr);
        
        //! Destructor
        virtual ~ColorComboBox();
        
        //! Gets the color
        QColor color() const;
        
        //! Sets the color
        void    setColor(QColor);
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    private:
        void    populate();
    };
}
