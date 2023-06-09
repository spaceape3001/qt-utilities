////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/DirBoxDelegate.hpp>
#include <gluon/edit/DirBox.hpp>

namespace yq::gluon {
    DirBoxDelegate::DirBoxDelegate(QObject*parent) : Delegate(parent)
    {
    }

    DirBoxDelegate::~DirBoxDelegate()
    {
    }

    yq::Compare   DirBoxDelegate::compare(const QVariant&a, const QVariant&b) const
    {
        return yq::compare(a.toString(), b.toString());
    }

    QWidget*    DirBoxDelegate::createEditor(QWidget* parent) const
    {
        return new DirBox(parent);
    }

    bool        DirBoxDelegate::setEditorData(QWidget*a, const QVariant&var) const
    {
        static_cast<DirBox*>(a) -> setDirPath(var.toString());
        return true;
    }
        
    QVariant    DirBoxDelegate::getEditorData(const QWidget*w) const
    {
        return static_cast<const DirBox*>(w) -> dirPath();
    }

    //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
    void        DirBoxDelegate::connectEditedSignal(QWidget*editor, QObject*other, const char*slot) const
    {
        connect(editor, SIGNAL(dirPathChanged(const QString&)), other, slot);
    }
}

