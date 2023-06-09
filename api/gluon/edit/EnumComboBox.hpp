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
    class GenericEnumComboBox : public ComboBox {
        Q_OBJECT
    public:
        
        GenericEnumComboBox(const yq::EnumDef*, QWidget*parent=nullptr);
        virtual ~GenericEnumComboBox();
        
        yq::Enum    enumValue() const;
        int         intValue() const;
        
        bool        setIntValue(int);
        bool        setEnumValue(yq::Enum);
        
    private:
        const yq::EnumDef* const    m_enum;
        yq::Map<int,int>            m_val2idx;
        yq::Map<int,int>            m_idx2val;
    };

    template <typename E>
    class EnumComboBox : public GenericEnumComboBox {
    public:
        EnumComboBox(QWidget*parent=nullptr) : GenericEnumComboBox( E::staticEnumInfo(), parent) 
        {
        }
        
        virtual ~EnumComboBox()
        {
        }
        
        void    setValue(E val)
        {
            GenericEnumComboBox::setIntValue(val.value());
        }
        
        E       value() const 
        {
            return E(GenericEnumComboBox::intValue());
        }
        
        void    set(const std::optional<E>& val,const E& def=E())
        {
            setValue(val?*val:def);
        }
        
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
