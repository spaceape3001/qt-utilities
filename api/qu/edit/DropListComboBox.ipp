////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL's QT UTILITIES
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <qu/edit/DropListComboBox.hpp>
#include <qu/core/IgCase.hpp>
#include <qu/core/Utilities.hpp>
#include <basic/Set.hpp>

#include <QAbstractItemView>
#include <QStandardItemModel>

namespace qu {
    struct DropListComboBox::Item {
        QStandardItem*  si  = nullptr;
        QString         key;
        bool            checked = false;
        Item(){}
        void            update()
        {
            if(si)
                si->setData(checked ? Qt::Checked : Qt::Unchecked);
        }
    };

    DropListComboBox::DropListComboBox(QWidget* parent) : ComboBox(parent), m_separator(", ")
    {
        connect(view(), &QAbstractItemView::pressed, this, &DropListComboBox::handlePressed);
    }

    void        DropListComboBox::setItems(const Set<QString,IgCase>&items)
    {
        if(!isSame(items)){
            m_items.clear();
            m_items.resize(items.size());
            m_model     = new QStandardItemModel(items.size(), 1, this);
            int     r   = 0;
            for(QString s : items){
                QStandardItem*it    = new QStandardItem(s);
                m_items[r].si       = it;
                it->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
                it->setData(Qt::Unchecked, Qt::CheckStateRole);
                m_model -> setItem(r++, 0, it);
            }
            setModel(m_model);
        }
    }


    DropListComboBox::~DropListComboBox()
    {
    }

    Set<QString,IgCase> DropListComboBox::checked() const
    {
        Set<QString,IgCase> ret;
        for(auto& i : m_items)
            if(i.checked)
                ret << i.key;
        return ret;
    }

    void        DropListComboBox::handlePressed(const QModelIndex&idx)
    {
        if((idx.row() >= 0) && (idx.row() < (int) m_items.size())){
            Item&   i   = m_items[idx.row()];
            i.checked   = !i.checked;
            i.update();
        }
        update();
    }

    bool        DropListComboBox::isSame(const Set<QString,IgCase>&items) const
    {
        if(items.size() != m_items.size())
            return false;
        int     r   = 0;
        for(QString s : items){
            if(!is_similar(m_items[r].key, s))
                return false;
            ++r;
        }
        return true;
    }

    void        DropListComboBox::setChecked(const Set<QString,IgCase>& them)
    {
        for(Item& i : m_items){
            i.checked   = them.has(i.key);
            i.update();
        }
        update();
    }


    void        DropListComboBox::setSeparator(const QString& sep)
    {
        m_separator     = sep;
        update();
    }

    void        DropListComboBox::update()
    {
        QString oldText     = currentText();
        QString newText     = joinQString(checked(), m_separator);
        if(oldText != newText)
            setEditText( newText);
    }
        
}



