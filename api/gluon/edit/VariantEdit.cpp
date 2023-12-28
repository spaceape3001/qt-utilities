////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////


#include "VariantEdit.hpp"
#include "ColorCombo.hpp"


//  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


VariantEdit::VariantEdit(QWidget* parent) : QWidget(parent)
{
}

VariantEdit::~VariantEdit()
{
}

QVariant        VariantEdit::value() const
{
    return QVariant();
}

void            VariantEdit::setQtType(int)
{
}

void            VariantEdit::setValue(const QVariant&)
{
}

void            VariantEdit::showTypeSelector(bool)
{
}

#ifdef YQ_QMAKE
    #include "moc_VariantEdit.cpp"
#endif
