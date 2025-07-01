////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/NullableDateDelegate.hpp>
#include <gluon/delegate/DelegateInfoWriter.hpp>
#include <gluon/edit/NullableDateEdit.hpp>

#include <QDate>

namespace yq::gluon {

    NullableDateDelegate::NullableDateDelegate(QObject*parent) : Delegate(parent)
    {
    }

    NullableDateDelegate::~NullableDateDelegate()
    {
    }
        
    yq::Compare     NullableDateDelegate::compare(const QVariant&va, const QVariant&vb) const
    {
        return yq::compare(va.toDate(), vb.toDate());
    }

    QWidget*    NullableDateDelegate::createEditor(QWidget* parent) const
    {
        return new NullableDateEdit(parent);
    }

    bool        NullableDateDelegate::setEditorData(QWidget*editor, const QVariant&val) const
    {
        static_cast<NullableDateEdit*>(editor)->setDate(val.toDate());
        return true;
    }

    QVariant    NullableDateDelegate::getEditorData(const QWidget*editor) const
    {
        return static_cast<const NullableDateEdit*>(editor)->date();
    }

    void        NullableDateDelegate::connectEditedSignal(QWidget*editor, QObject*obj, const char*slot) const
    {
        connect(editor, SIGNAL(editingFinished()), obj, slot);
    }

    QVariant    NullableDateDelegate::render(const QVariant&input) const 
    {
        QDate d =  input.value<QDate>();
        if(d.isNull())
            return QVariant();
        return d.toString(Qt::ISODate);
    }

    void NullableDateDelegate::init_meta()
    {
        auto w = writer<NullableDateDelegate>();
        w.description("Nullable Date Delegate");
        w.declare_type<QDate>();
    }
}

YQ_OBJECT_IMPLEMENT(yq::gluon::NullableDateDelegate)
#include "moc_NullableDateDelegate.cpp"
