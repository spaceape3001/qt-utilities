////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/StringDelegate.hpp>
#include <gluon/delegate/DelegateMetaWriter.hpp>
#include <gluon/core/Utilities.hpp>
#include <gluon/edit/LineEdit.hpp>

namespace yq::gluon {
    StringDelegate::StringDelegate(QObject*parent) : StringDelegate(nullptr, parent)
    {
    }
        
    StringDelegate::StringDelegate(QValidator*valid, QObject*parent) : Delegate(parent), m_validator(valid)
    {
    }

    StringDelegate::~StringDelegate()
    {
    }

    yq::Compare   StringDelegate::compare(const QVariant&a, const QVariant&b) const
    {
        return compare_igCase(a.toString(), b.toString());
    }

    QWidget*    StringDelegate::createEditor(QWidget* parent) const
    {
        LineEdit*   le  =  new LineEdit(parent);
        if(m_validator)
            le -> setValidator(m_validator);
        return le;
    }

    bool        StringDelegate::setEditorData(QWidget*wid, const QVariant&val) const
    {
        static_cast<LineEdit*>(wid) -> setText(val.toString());
        return true;
    }

    QVariant    StringDelegate::getEditorData(const QWidget*wid) const 
    {
        return static_cast<const LineEdit*>(wid) -> text();
    }

    void        StringDelegate::connectEditedSignal(QWidget*editor, QObject*other, const char*slot) const
    {
        connect(editor, SIGNAL(textEdited(const QString&)), other, slot);
    }

    void StringDelegate::init_meta()
    {
        auto w = writer<StringDelegate>();
        w.description("String Delegate");
        w.declare_type<QString>();
    }
}

YQ_OBJECT_IMPLEMENT(yq::gluon::StringDelegate)
#include "moc_StringDelegate.cpp"
