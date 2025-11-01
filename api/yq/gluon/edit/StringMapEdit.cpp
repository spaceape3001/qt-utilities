////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "StringMapEdit.hpp"
#include "StringMapEditModel.hpp"
#include "StringMapEditView.hpp"

#include <yq/gluon/core/IgCaseQ.hpp>
#include <yq/gluon/core/Utilities.hpp>
#include <yq/container/Vector.hpp>
#include <yq/container/Map.hpp>

#include <QHeaderView>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <set>

namespace yq::gluon {

    struct StringMapEdit::Item { 
        QString key, value; 
        Item(){}
        Item(const QString& _k, const QString& _d) : key(_k), value(_d){}	
    };



    StringMapEdit::StringMapEdit(QWidget* parent) : 
        QWidget(parent), 
        m_model(new Model), 
        m_view(new View(m_model))
    {
        QPushButton*	add		= new QPushButton("Add");
        connect(add, &QPushButton::pressed, m_model, &StringMapEdit::Model::addRow);
        QPushButton*	rem		= new QPushButton("Del");
        connect(rem, &QPushButton::pressed, this, &StringMapEdit::delRow);

        QVBoxLayout*    mlay    = new QVBoxLayout;
        mlay->addWidget(m_view, 1);
        QHBoxLayout*	hlay	= new QHBoxLayout;
        hlay->addWidget(add);
        hlay->addWidget(rem);
        setLayout(mlay);
    }

    StringMapEdit::~StringMapEdit()
    {
    }

    void		StringMapEdit::delRow()
    {
        std::vector<int>	rows	= m_view->selectedRows();
        if(!rows.empty())
            m_model->removeRows(rows);
    }

    QStringMap	StringMapEdit::get() const
    {
        return m_model->get();
    }

    void		StringMapEdit::set(const QStringMap&v)
    {
        m_model->set(v);
    }


    //	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


    StringMapEdit::Model::Model()
    {
        m_key.label      = tr("Key");
        m_value.label    = tr("Value");
    }

    StringMapEdit::Model::~Model()
    {
    }

    int StringMapEdit::Model::columnCount(const QModelIndex&) const 
    {
        return MAX_COLS;
    }

    int StringMapEdit::Model::rowCount(const QModelIndex&) const
    {
        return m_items.size();
    }
        
    QVariant StringMapEdit::Model::data(const QModelIndex&idx, int role) const 
    {
        if((role != Qt::DisplayRole) && (role != Qt::EditRole))
            return QVariant();
        if(idx.row() < 0)
            return QVariant();
        if(idx.row() >= (int) m_items.size())
            return QVariant();
            
        switch(idx.column()){
        case ColKey:
            return m_items[idx.row()].key;
        case ColValue:
            return m_items[idx.row()].value;
        default:
            return QVariant();
        }
    }

    bool StringMapEdit::Model::setData(const QModelIndex&idx, const QVariant&var, int role)
    {
        int r	= idx.row();
        if(role != Qt::EditRole)
            return false;
        if(r < 0)
            return false;
        if(r >= (int) m_items.size())
            return false;
        auto& row	= m_items[r];
        QString	val	= var.toString();
        
        switch(idx.column()){
        case ColKey:
            if(m_key.validator && !m_key.validator(val))
                return false;

            if(row.key == val)
                return false;
            if(has(val))        // duplication
                return false;
            row.key = val;
            emit dataChanged(idx, idx);
            return true;
        case ColValue:
            if(m_value.validator && !m_value.validator(val))
                return false;
            if(row.value == val)
                return false;
            row.value		= val;
            emit dataChanged(idx, idx);
            return true;
        default:
            return false;
        }
    }

    QVariant StringMapEdit::Model::headerData(int n, Qt::Orientation ori, int role) const 
    {
        if(role != Qt::DisplayRole)
            return QVariant();
        if(ori != Qt::Horizontal)
            return QVariant();
        switch(n){
        case ColKey:
            return m_key.label;
        case ColValue:
            return m_value.label;
        default:
            return QVariant();
        }
    }

    Qt::ItemFlags StringMapEdit::Model::flags(const QModelIndex&) const 
    {
        return Qt::ItemIsEditable|Qt::ItemIsEnabled;
    }

    bool			StringMapEdit::Model::has(const QString&k) const
    {
        for(auto& i : m_items)
            if(is_similar(i.key, k))
                return true;
        return false;
    }

    QStringMap		StringMapEdit::Model::get() const
    {
        QStringMap	ret;
        for(auto& i : m_items){
            if(i.key.isEmpty())
                continue;
            ret[i.key]	= i.value;
        }
        return ret;
    }

    void			StringMapEdit::Model::set(const QStringMap&k)
    {
        beginResetModel();
        m_items.clear();
        for(auto& i : k)
            m_items.push_back(Item(i.first, i.second));
        endResetModel();
    }

    void        StringMapEdit::Model::setKeyLabel(const QString&v)
    {
        m_key.label  = v;
        //  This *MAY* need a model reset?
    }
    
    void        StringMapEdit::Model::setKeyValidator(Validator v)
    {
        m_key.validator = v;
    }
    
    void        StringMapEdit::Model::setValueLabel(const QString&v)
    {
        m_value.label    = v;
        //  This *MAY* need a model reset?
    }

    void        StringMapEdit::Model::setValueValidator(Validator v)
    {
        m_value.validator = v;
    }

    void		StringMapEdit::Model::addRow()
    {
        if(has(QString()))
            return ;
        int 	n	 = (int) m_items.size();
        beginInsertRows(QModelIndex(), n, n);
        m_items.push_back(Item());
        endInsertRows();
    }

    void			StringMapEdit::Model::removeRows(std::span<int> toRemove)
    {
        if(toRemove.empty())
            return ;
            
        Vector<int>		rem(toRemove.begin(), toRemove.end());
        rem.sort([](int a, int b) -> bool { return a > b; } );	// reverse order
        rem.unique();
        
        for(int i : rem){
            beginRemoveRows(QModelIndex(), i, i);
            m_items.erase_at((size_t) i);
            endRemoveRows();
        }
    }

    //	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    StringMapEdit::View::View(Model*mo)
    {
        setModel(mo);
        setAlternatingRowColors(true);
        setSelectionBehavior(SelectRows);
        setShowGrid(true);
        horizontalHeader()->setStretchLastSection(true);
    }

    StringMapEdit::View::~View()
    {
    }

    std::vector<int>	StringMapEdit::View::selectedRows() const
    {
        std::set<int>	ret;
        QItemSelectionModel*		smode	= selectionModel();
        if(smode){
            for(auto& i : smode->selectedRows())
                ret.insert(i.row());
        }
        return std::vector<int>(ret.begin(), ret.end());
    }
}


#include "moc_StringMapEdit.cpp"
#include "moc_StringMapEditModel.cpp"
#include "moc_StringMapEditView.cpp"
