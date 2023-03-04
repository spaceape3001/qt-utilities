////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <qu/undo/ComboBox.hpp>

namespace qu {
    ComboBox::ComboBox(QWidget* parent) : QComboBox(parent)
    {
    }

    ComboBox::~ComboBox()
    {
    }

    void    ComboBox::reset()
    {
        setCurrentIndex(-1);
    }
}

#ifdef YQ_QMAKE
    #include "moc_ComboBox.cpp"
#endif
