////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/DoubleSpinBox.hpp>

namespace qu {
    DoubleSpinBox::DoubleSpinBox(QWidget*parent) : QDoubleSpinBox(parent)
    {
    }

    DoubleSpinBox::~DoubleSpinBox()
    {
    }

    void    DoubleSpinBox::reset()
    {
        setValue(0);
    }
}


