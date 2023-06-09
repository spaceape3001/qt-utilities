////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <gluon/delegate/EnumComboBoxDelegate.hpp>
#include <gluon/edit/EnumComboBox.hpp>
#include <gluon/core/Utilities.hpp>

namespace yq::gluon {
    GenericEnumComboBoxDelegate::GenericEnumComboBoxDelegate(const yq::EnumDef*def, int type, QObject *parent) : 
        Delegate(parent), m_enum(def), m_type(type)
    {
    }

    GenericEnumComboBoxDelegate::~GenericEnumComboBoxDelegate()
    {
    }

    void        GenericEnumComboBoxDelegate::connectEditedSignal(QWidget* editor, QObject* other, const char* slot) const
    {
        connect(editor, SIGNAL(fileChanged(const QString&)), other, slot);
    }

    QWidget*    GenericEnumComboBoxDelegate::createEditor(QWidget* parent) const
    {
        return new GenericEnumComboBox(m_enum, parent);
    }

    QString 	GenericEnumComboBoxDelegate::displayText(const QVariant &value, const QLocale &locale) const
    {
        return render(value).toString();
    }

    QVariant    GenericEnumComboBoxDelegate::getEditorData(const QWidget* wid) const
    {
        int i   = static_cast<const GenericEnumComboBox*>(wid) -> intValue();
        return QVariant(m_type, &i);
    }

    QVariant    GenericEnumComboBoxDelegate::render(const QVariant&var) const 
    {
        if((var.userType() == m_type ) || var.userType() == QMetaType::Int){
            int i   = *((const int*) var.constData());
            QString txt = qString(m_enum -> key_of(i));
            return txt;
        } else
            return var;
    }

    bool        GenericEnumComboBoxDelegate::setEditorData(QWidget*wid, const QVariant&val) const
    {
        if((val.userType() == m_type ) || val.userType() == QMetaType::Int){
            static_cast<GenericEnumComboBox*>(wid) -> setIntValue(*((const int*) val.constData()));
            return true;
        } else if(val.userType() == QMetaType::QString){
            std::string s   = val.toString().toStdString();
            auto    i   = m_enum -> value_of( s);
            if(i)
                static_cast<GenericEnumComboBox*>(wid) -> setIntValue(*i);
            return i.has_value();
        } else
            return false;
    }

    //bool        GenericEnumComboBoxDelegate::paint(QPainter*painter, const QStyleOptionViewItem& option, const QVariant&var) const
    //{
        //if((var.userType() == m_type ) || var.userType() == QMetaType::Int){
            //int i   = *((const int*) var.constData());
            //QString txt = m_enum -> keyOf(i);
            //return Delegate::paint(painter, option, txt);
        //} else
            //return Delegate::paint(painter, option, var);
    //}

}

