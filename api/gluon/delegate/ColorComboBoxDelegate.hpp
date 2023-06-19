////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {

    class  ColorComboBoxDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(ColorComboBoxDelegate, Delegate)
    public:

        using DataType = QColor;

        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        virtual QVariant    getEditorData(const QWidget*) const;
        virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;

        ColorComboBoxDelegate(QObject* parent=nullptr);
        virtual ~ColorComboBoxDelegate();
    };
}
