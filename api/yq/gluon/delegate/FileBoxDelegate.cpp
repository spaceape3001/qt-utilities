////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/delegate/FileBoxDelegate.hpp>
#include <yq/gluon/delegate/DelegateMetaWriter.hpp>
#include <yq/gluon/edit/FileBox.hpp>

namespace yq::gluon {
    FileBoxDelegate::FileBoxDelegate(QObject*parent) : Delegate(parent)
    {
    }

    FileBoxDelegate::~FileBoxDelegate()
    {
    }

    yq::Compare     FileBoxDelegate::compare(const QVariant&a, const QVariant&b) const
    {
        return yq::compare(a.toString(), b.toString());
    }

    QWidget*    FileBoxDelegate::createEditor(QWidget* parent) const
    {
        return new FileBox(parent);
    }

    bool        FileBoxDelegate::setEditorData(QWidget*a, const QVariant&var) const
    {
        static_cast<FileBox*>(a) -> setFile(var.toString());
        return true;
    }
        
    QVariant    FileBoxDelegate::getEditorData(const QWidget*w) const
    {
        return static_cast<const FileBox*>(w) -> file();
    }

    //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
    void        FileBoxDelegate::connectEditedSignal(QWidget*editor, QObject*other, const char*slot) const
    {
        connect(editor, SIGNAL(fileChanged(const QString&)), other, slot);
    }

    void FileBoxDelegate::init_meta()
    {
        auto w = writer<FileBoxDelegate>();
        w.description("File Box delegate");
    }
}

YQ_OBJECT_IMPLEMENT(yq::gluon::FileBoxDelegate)
#include "moc_FileBoxDelegate.cpp"
