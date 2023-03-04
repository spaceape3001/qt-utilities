////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <qu/undo/CheckBox.hpp>

namespace qu {
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

#ifdef YQ_QMAKE
    #include "moc_CheckBox.cpp"
#endif
