////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/NullableDateEdit.hpp>
#include <qu/edit/CheckBox.hpp>
#include <qu/edit/DateEdit.hpp>

#include <QHBoxLayout>

namespace qu {
    NullableDateEdit::NullableDateEdit(QWidget*parent) : QWidget(parent)
    {
        QHBoxLayout*    lay = new QHBoxLayout;
        m_good      = new CheckBox;
        m_date      = new DateEdit;
        
        m_null      = true;
        m_good->setChecked(false);
        m_date->setEnabled(false);
        m_date->setDisplayFormat("yyyy-MM-dd");
        
        setContentsMargins(0,0,0,0);
        lay->setContentsMargins(0,0,0,0);
        
        lay->addWidget(m_good, 0);
        lay->addWidget(m_date, 1);
        setLayout(lay);
        connect(m_good, &CheckBox::stateChanged, this, &NullableDateEdit::stateChanged);
        connect(m_date, &QDateEdit::editingFinished, this, &NullableDateEdit::editingFinished);
    }


    NullableDateEdit::~NullableDateEdit()
    {
    }

    void        NullableDateEdit::setDisplayFormat(const QString&s)
    {
        m_date->setDisplayFormat(s);
    }


    QDate       NullableDateEdit::date() const
    {
        if(m_null)
            return QDate();
        return m_date->date();
    }

    void        NullableDateEdit::stateChanged(int ch)
    {
        if(ch){
            if(m_null){
                m_date->setEnabled(true);
                m_null  = false;
                emit editingFinished();
            }
        } else {
            if(!m_null){
                m_date->setEnabled(false);
                m_null  = true;
                emit    editingFinished();
            }
        }
    }

    void        NullableDateEdit::setDate(const QDate&dt)
    {
        if(dt != date()){
            if(dt.isNull()){
                m_null  = true;
                m_good  ->setChecked(false);
                m_date  ->setEnabled(false);
            } else {
                m_null  = false;
                m_good  ->setChecked(true);
                m_date  ->setEnabled(true);
                m_date  ->setDate(dt);
            }
        }
    }
}

