////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>
#include <basic/Enum.hpp>
#include <QMetaType>

namespace yq::gluon {
    /*! \brief Enumeration Delegate

        The render/create can be any of integer, string, and/or the enumeration.
        The setData will be in the enum type.
    */
    class GenericEnumComboBoxDelegate : public Delegate {
        Q_OBJECT
    public:
        GenericEnumComboBoxDelegate(const EnumDef*, QMetaType type, QObject *parent=nullptr);
        ~GenericEnumComboBoxDelegate();
        
        virtual QVariant    render(const QVariant&) const override;
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        virtual QVariant    getEditorData(const QWidget*) const;
        //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;
        virtual QString 	displayText(const QVariant &value, const QLocale &locale) const override;    

    private:
        const EnumDef*      m_enum = nullptr;
        QMetaType           m_type;
    };

    template <typename E>
    class EnumComboBoxDelegate : public GenericEnumComboBoxDelegate {
    public:
        using DataType = E;

        EnumComboBoxDelegate(QObject*parent=nullptr) : GenericEnumComboBoxDelegate( E::staticEnumInfo(), qMetaTypeId<E>(), parent ) 
        {
        }
        
        virtual ~EnumComboBoxDelegate()
        {
        }
    };
}
