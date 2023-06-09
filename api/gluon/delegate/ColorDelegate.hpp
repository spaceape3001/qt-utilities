////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Delegate.hpp"

namespace yq::gluon {

    class  ColorDelegate : public Delegate {
        Q_OBJECT
    public:


        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        virtual QVariant    getEditorData(const QWidget*) const;
        virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;

        ColorDelegate(QObject* parent=nullptr);
        virtual ~ColorDelegate();
    };
}
