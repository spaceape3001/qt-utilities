////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/edit/ComboBox.hpp>
#include <basic/Enum.hpp>
#include <basic/Map.hpp>
#include <optional>

namespace yq::gluon {

    /*! \brief Generic Enumeration Combo Box 
    
        Simple drop-down that leverages an enum definition to populate
        the combo box options
    */
    class GenericEnumComboBox : public ComboBox {
        Q_OBJECT
    public:
      
        /*! Constructor
        
            \param[in] eDef         Enumeration Definition
            \param[in] parent   Parent widget
        */
        GenericEnumComboBox(const EnumDef* eDef, QWidget*parent=nullptr);
        
        //! Destructor
        virtual ~GenericEnumComboBox();
        
        //! Gets the enumeration value (generically)
        Enum        enumValue() const;
        
        //! Gets the enumeration value as an integer
        int         intValue() const;
        
        //! Sets the enumeration value as an integer
        bool        setIntValue(int);
        
        //! Sets the enumeration value as a generic enumeration
        bool        setEnumValue(yq::Enum);
        
    private:
        const EnumDef* const    m_enum;
        Map<int,int>            m_val2idx;
        Map<int,int>            m_idx2val;
    };

    /*! \brief Enumeration Combo Box
    
        This is the specifically bound enumeration combo box.
        
        \note The Qt object system won't know this name because 
        it's not a fully resolved type.
        
        \tparam[E]  The enumeration
    */
    template <typename E>
    class EnumComboBox : public GenericEnumComboBox {
    public:
    
        //! Constructor
        EnumComboBox(QWidget*parent=nullptr) : GenericEnumComboBox( E::staticEnumInfo(), parent) 
        {
        }
        
        //! Destructor
        virtual ~EnumComboBox()
        {
        }
        
        //! Sets the value
        void    setValue(E val)
        {
            GenericEnumComboBox::setIntValue(val.value());
        }
        
        //! Gets the current value
        E       value() const 
        {
            return E(GenericEnumComboBox::intValue());
        }
        
        //! Sets the value as an optional with a default value
        void    set(const std::optional<E>& val,const E& def=E())
        {
            setValue(val?*val:def);
        }
        
        //! Gets the value, if *NOT* the default, otherwise empty
        std::optional<E> get(const E& def=E()) const
        {
            std::optional<E> ret;
            E   val = value();
            if(val != def)
                ret = val;
            return ret;
        }
    };

}
