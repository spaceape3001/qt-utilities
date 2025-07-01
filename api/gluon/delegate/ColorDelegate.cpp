////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/ColorDelegate.hpp>
#include <gluon/delegate/DelegateMetaWriter.hpp>
#include <QColorDialog>
#include <QPainter>

namespace yq::gluon {

    ColorDelegate::ColorDelegate(QObject* parent) : Delegate(parent)
    {
    }

    ColorDelegate::~ColorDelegate()
    {
    }


    QWidget*    ColorDelegate::createEditor(QWidget* parent) const
    {
        return new QColorDialog(parent);
    }

    bool        ColorDelegate::setEditorData(QWidget*editor, const QVariant&val) const
    {
        QColorDialog*       cc  = static_cast<QColorDialog*>(editor);
        QColor      v   = val.value<QColor>();
        if(v != cc->currentColor())
            cc->setCurrentColor(v);
        return true;
    }

    QVariant    ColorDelegate::getEditorData(const QWidget*editor) const
    {
        return static_cast<const QColorDialog*>(editor)->currentColor();
    }

    bool        ColorDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QVariant& val) const
    {
        QColor  color   = val.value<QColor>();
        if(!color.isValid()){
            painter->drawLine(QLine(option.rect.left(), option.rect.top(), option.rect.right(), option.rect.bottom()));
            painter->drawLine(QLine(option.rect.left(), option.rect.bottom(), option.rect.right(), option.rect.top()));
        } else
            painter->fillRect(option.rect, color);
        return true;
    }

    void        ColorDelegate::connectEditedSignal(QWidget*editor, QObject*other, const char*slot) const
    {
        connect(editor, SIGNAL(currentColorChanged(const QColor&)), other, slot);
        connect(editor, SIGNAL(colorSelected(const QColor&)), other, slot);
    }

    void ColorDelegate::init_meta()
    {
        auto w = writer<ColorDelegate>();
        w.description("Color Delegate");
    }
    
}

YQ_OBJECT_IMPLEMENT(yq::gluon::ColorDelegate)

#include "moc_ColorDelegate.cpp"
