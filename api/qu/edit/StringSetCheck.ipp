////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/StringSetCheck.hpp>
#include <qu/edit/CheckBox.hpp>
#include <qu/layout/FlowLayout.hpp>
#include <basic/Set.hpp>
#include <basic/Vector.hpp>

namespace qu {

    StringSetCheck::StringSetCheck(QWidget* parent) : QWidget(parent)
    {
        m_layout        = new FlowLayout;
        setLayout(m_layout);
    }

    StringSetCheck::~StringSetCheck()
    {
    }
        
    void                StringSetCheck::setItems(const StringSet& items)
    {
        if(makeVector(items) != m_checks.keys()){
            m_layout -> clear();
            for(QString i : items){
                CheckBox*   cb  = new CheckBox(i);
                m_checks[i] = cb;
                m_layout -> addWidget(cb);
                connect(cb, &QCheckBox::stateChanged, this, &StringSetCheck::changed);
            }
        } else {
            for(auto& i : m_checks)
                i.second -> setChecked(false);
        }
    }

    void                StringSetCheck::setChecked(const StringSet& items)
    {
        for(auto& i : m_checks){
            if(!i.second -> isTristate())
                i.second -> setChecked(items.has(i.first));
        }
    }

    void                StringSetCheck::setFixed(const StringSet& items)
    {
        for(auto& i : m_checks){
            if(items.has(i.first)){
                i.second -> setTristate(true);
                i.second -> setCheckState(Qt::PartiallyChecked);
            } else {
                if(i.second -> checkState() == Qt::PartiallyChecked)
                    i.second -> setCheckState(Qt::Unchecked);
                i.second -> setTristate(false);
            }
        }
    }


    StringSet StringSetCheck::checked(bool fIncFixed) const
    {
        StringSet ret;
        if(fIncFixed){
            for(auto& i : m_checks)
                if(i.second -> checkState() != Qt::Unchecked)
                    ret << i.first;
        } else {
            for(auto& i : m_checks)
                if(i.second -> checkState() == Qt::Checked)
                    ret << i.first;
        }
        return ret;
    }

    void       StringSetCheck::clear()
    {
        for(auto & i : m_checks)
            i.second -> setChecked(false);
    }

    void        StringSetCheck::setReadOnly(bool f)
    {
        setEnabled(!f);
        for(auto& i : m_checks)
            i.second -> setEnabled(!f);
    }
}

