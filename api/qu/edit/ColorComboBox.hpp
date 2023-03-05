////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/ComboBox.hpp>

class QColor;

namespace qu {

    class ColorComboBox : public ComboBox {
        Q_OBJECT
        Q_PROPERTY(QColor color READ color WRITE setColor USER true)
    public:
        ColorComboBox(QWidget* parent=nullptr);
        virtual ~ColorComboBox();
        
        QColor color() const;
        void    setColor(QColor);
        
        //  TODO: Currently, the *ACTUAL* undo tie in is not yet implemented

    private:
        void    populate();
    };
}
