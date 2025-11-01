////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/edit/DoubleSpinBox.hpp>

namespace yq::gluon {
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

#include "moc_DoubleSpinBox.cpp"
