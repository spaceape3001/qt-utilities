////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/edit/CheckBox.hpp>

namespace yq::gluon {
    CheckBox::CheckBox(QWidget* parent) : QCheckBox(parent)
    {
    }

    CheckBox::CheckBox(const QString& text, QWidget* parent) : QCheckBox(text, parent)
    {
    }

    CheckBox::~CheckBox()
    {
    }

    bool    CheckBox::isChecked() const
    {
        return checkState() ? true : false;
    }

    void    CheckBox::setChecked(bool f)
    {
        setCheckState(f?Qt::Checked:Qt::Unchecked);
    }
}

#include "moc_CheckBox.cpp"
