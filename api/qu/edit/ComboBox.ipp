////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/ComboBox.hpp>

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

