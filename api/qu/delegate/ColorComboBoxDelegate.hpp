////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/delegate/Delegate.hpp>

namespace qu {

    class  ColorComboBoxDelegate : public Delegate {
        Q_OBJECT
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
