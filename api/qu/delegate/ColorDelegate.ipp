////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/delegate/ColorDelegate.hpp>
#include <QColorDialog>
#include <QPainter>

namespace qu {

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
}

