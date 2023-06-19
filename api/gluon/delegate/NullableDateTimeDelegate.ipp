////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/NullableDateTimeDelegate.hpp>
#include <gluon/edit/NullableDateTimeEdit.hpp>
#include <QDateTime>

namespace yq::gluon {

    NullableDateTimeDelegate::NullableDateTimeDelegate(QObject*parent) : Delegate(parent)
    {
    }

    NullableDateTimeDelegate::~NullableDateTimeDelegate()
    {
    }
        
    yq::Compare     NullableDateTimeDelegate::compare(const QVariant&va, const QVariant&vb) const
    {
        return yq::compare(va.toDateTime(), vb.toDateTime());
    }

    QWidget*    NullableDateTimeDelegate::createEditor(QWidget* parent) const
    {
        return new NullableDateTimeEdit(parent);
    }

    bool        NullableDateTimeDelegate::setEditorData(QWidget*editor, const QVariant&val) const
    {
        static_cast<NullableDateTimeEdit*>(editor)->setDateTime(val.toDateTime());
        return true;
    }

    QVariant    NullableDateTimeDelegate::getEditorData(const QWidget*editor) const
    {
        return static_cast<const NullableDateTimeEdit*>(editor)->dateTime();
    }

    void        NullableDateTimeDelegate::connectEditedSignal(QWidget*editor, QObject*obj, const char*slot) const
    {
        connect(editor, SIGNAL(editingFinished()), obj, slot);
    }

    QVariant    NullableDateTimeDelegate::render(const QVariant&input) const 
    {
        QDateTime d =  input.value<QDateTime>();
        if(d.isNull())
            return QVariant();
        return d.toString(Qt::ISODate);
    }
}


