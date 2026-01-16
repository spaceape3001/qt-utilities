////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/edit/EnumComboBox.hpp>
#include <yq/gluon/core/ustring.hpp>
#include <cassert>

namespace yq::gluon {

    GenericEnumComboBox::GenericEnumComboBox(const yq::EnumDef*def, QWidget*parent) : ComboBox(parent), m_enum(def)
    {
        assert(def);
        
        int     i   = 0;
        for(std::string_view k : m_enum -> all_keys()){
            auto val        = m_enum -> value_of(k);
            if(!val)
                continue;
                
            addItem(qString(k));
            m_idx2val[i]    = *val;
            m_val2idx[*val]  = i;
            ++i;
        }
        setIntValue(m_enum -> default_value());
    }

    GenericEnumComboBox::~GenericEnumComboBox()
    {
    }

    yq::Enum    GenericEnumComboBox::enumValue() const
    {
        int     i   = currentIndex();
        auto itr    = m_idx2val.find(i);
        if(itr != m_idx2val.end())
            return m_enum -> make_enum(itr -> second);
        else
            return yq::Enum();
    }

    int     GenericEnumComboBox::intValue() const
    {
        return m_idx2val.get(currentIndex(), m_enum -> default_value());
    }


    bool    GenericEnumComboBox::setIntValue(int v)
    {
        int i       = m_val2idx.get( v, -1);
        if(i >= 0){
            setCurrentIndex(i);
            return true;
        } else
            return false;
    }

    bool    GenericEnumComboBox::setEnumValue(yq::Enum e)
    {
        if(e.definition() != m_enum)
            return false;
        return setIntValue(e.value());
    }
}

#include "moc_EnumComboBox.cpp"
