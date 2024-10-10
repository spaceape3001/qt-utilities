////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/delegate/Delegate.hpp>
#include <yq/core/Enum.hpp>
#include <QMetaType>

namespace yq::gluon {
    /*! \brief Generic Enumeration Delegate

        The render/create can be any of integer, string, and/or the enumeration.
        The setData will be in the enum type.
    */
    class GenericEnumComboBoxDelegate : public Delegate {
        Q_OBJECT
        YQ_OBJECT_DECLARE(GenericEnumComboBoxDelegate, Delegate)
    public:
    
        //! Constructor
        GenericEnumComboBoxDelegate(const EnumDef*, QMetaType type, QObject *parent=nullptr);
        ~GenericEnumComboBoxDelegate();
        
        //! Renders the data
        virtual QVariant    render(const QVariant&) const override;
        
        //! Creates an editor
        virtual QWidget*    createEditor(QWidget* parent=nullptr) const;
        
        //! Sets editor data
        virtual bool        setEditorData(QWidget*, const QVariant&) const;
        
        //! Gets editor data
        virtual QVariant    getEditorData(const QWidget*) const;
        //virtual bool        paint(QPainter*, const QStyleOptionViewItem& option, const QVariant&) const;
        
        //! Connects the edited signal
        virtual void        connectEditedSignal(QWidget*, QObject*, const char*) const;
        
        //! Display text for value
        virtual QString 	displayText(const QVariant &value, const QLocale &locale) const override;    

    private:
        const EnumDef*      m_enum = nullptr;
        QMetaType           m_type;
    };


    /*! \brief Specific enum combo box delegate
    
        This is the derivation to Generic, binding to a specific enumeration type by meta info
    */
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
