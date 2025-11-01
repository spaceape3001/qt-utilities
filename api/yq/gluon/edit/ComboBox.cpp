////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/edit/ComboBox.hpp>

namespace yq::gluon {
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

#include "moc_ComboBox.cpp"
