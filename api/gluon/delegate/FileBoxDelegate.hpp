////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>

namespace yq::gluon {
    class FileBoxDelegate : public Delegate {
        Q_OBJECT
    public:
        FileBoxDelegate(QObject*parent =nullptr);
        ~FileBoxDelegate();
        virtual yq::Compare compare(const QVariant&, const QVariant&) const override; 
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        virtual QVariant    getEditorData(const QWidget*) const;
        //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;
    };
}



