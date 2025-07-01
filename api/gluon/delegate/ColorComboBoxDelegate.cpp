////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/ColorComboBoxDelegate.hpp>
#include <gluon/delegate/DelegateMetaWriter.hpp>
#include <gluon/edit/ColorComboBox.hpp>
#include <QPainter>

namespace yq::gluon {

    ColorComboBoxDelegate::ColorComboBoxDelegate(QObject* parent) : Delegate(parent)
    {
    }

    ColorComboBoxDelegate::~ColorComboBoxDelegate()
    {
    }


    QWidget*    ColorComboBoxDelegate::createEditor(QWidget* parent) const
    {
        return new ColorComboBox(parent);
    }

    bool        ColorComboBoxDelegate::setEditorData(QWidget*editor, const QVariant&val) const
    {
        ColorComboBox*       cc  = static_cast<ColorComboBox*>(editor);
        QColor      v   = val.value<QColor>();
        if(v != cc->color())
            cc->setColor(v);
        return true;
    }

    QVariant    ColorComboBoxDelegate::getEditorData(const QWidget*editor) const
    {
        return static_cast<const ColorComboBox*>(editor)->color();
    }

    bool        ColorComboBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QVariant& val) const
    {
        QColor  color   = val.value<QColor>();
        if(!color.isValid()){
            painter->drawLine(QLine(option.rect.left(), option.rect.top(), option.rect.right(), option.rect.bottom()));
            painter->drawLine(QLine(option.rect.left(), option.rect.bottom(), option.rect.right(), option.rect.top()));
        } else
            painter->fillRect(option.rect, color);
        return true;
    }

    void        ColorComboBoxDelegate::connectEditedSignal(QWidget*editor, QObject*other, const char*slot) const
    {
        connect(editor, SIGNAL(currentTextChanged(int)), other, slot);
        connect(editor, SIGNAL(currentIndexChanged(int)), other, slot);
    }
    
    void ColorComboBoxDelegate::init_meta()
    {
        auto w = writer<ColorComboBoxDelegate>();
        w.declare_type<QColor>();
    }

}

YQ_OBJECT_IMPLEMENT(yq::gluon::ColorComboBoxDelegate)

#include "moc_ColorComboBoxDelegate.cpp"
