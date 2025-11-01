////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/model/RowTableModel.hpp>
#include <yq/gluon/model/ColumnModel.hpp>
#include <yq/algorithm/DiffEngine.hpp>
#include <yq/gluon/core/Utilities.hpp>
#include <yq/gluon/delegate/Delegate.hpp>

namespace yq::gluon {
    template <typename T, typename ... P>
    struct RowTableModel<T, P...>::Column {
        ColumnModel<T,P...> model;
        ColOptions          options;
        Delegate*           delegate = nullptr;
        int                 deltries = 0;
    };
    
    template <typename T, typename ... P>
    RowTableModel<T, P...>::RowTableModel(P... params) : m_params(params...)
    {
    }

    template <typename T, typename ... P>
    RowTableModel<T, P...>::RowTableModel(QObject*parent, P... params) : QAbstractTableModel(parent), m_params(params...)
    {
    }

    template <typename T, typename ... P>
    RowTableModel<T, P...>::RowTableModel(std::initializer_list<const char*> cols, P... params) : m_params(params...)
    {
        setColumns(cols);
    }
    
    template <typename T, typename ... P>
    RowTableModel<T, P...>::RowTableModel(std::initializer_list<const char*>cols, QObject*parent, P... params) :
        QAbstractTableModel(parent), m_params(params...)
    {
        setColumns(cols);
    }

    template <typename T, typename ... P>
    RowTableModel<T, P...>::~RowTableModel()
    {
        for(Column& c : m_columns){
            if(c.delegate){
                c.delegate->deleteLater();
                c.delegate  = nullptr;
            }
        }
    }


    template <typename T, typename ... P>
    void    RowTableModel<T, P...>::_changed()
    {
        if((!m_rows.empty()) && (!m_columns.empty())){
            dataChanged(
                createIndex(0,0),
                createIndex(m_rows.size()-1, m_columns.size()-1)
            );
        }
    }

    template <typename T, typename ... P>
    const RowTableModel<T, P...>::Column*   RowTableModel<T, P...>::column(int n) const
    {
        if(n<0)
            return nullptr;
        if(n>=(int) m_columns.size())
            return nullptr;
        return &m_columns[(size_t) n];
    }

    template <typename T, typename ... P>
    RowTableModel<T, P...>::Column*   RowTableModel<T, P...>::column(int n) 
    {
        if(n<0)
            return nullptr;
        if(n>=(int) m_columns.size())
            return nullptr;
        return &m_columns[(size_t) n];
    }

    template <typename T, typename ... P>
    const RowTableModel<T, P...>::Column*   RowTableModel<T, P...>::column(const QModelIndex&idx) const
    {
        return column(idx.column());
    }

    template <typename T, typename ... P>
    int     RowTableModel<T, P...>::columnCount(const QModelIndex&) const 
    {
        return (int) m_columns.size();
    }

    template <typename T, typename ... P>
    QVariant RowTableModel<T, P...>::data(const QModelIndex& idx, int role) const 
    {
        const Column*   c   = column(idx);
        if(!c)
            return QVariant();
        
        const T*      r   = row(idx);
        switch(role){
        case Qt::DisplayRole:
            if(!r)
                return c->model.addMsg;
            return c->model.display(*r, m_params);
        case Qt::EditRole:
            if(!r)
                return c->model.defVal;
            return c->model.edit(*r, m_params);
        case Qt::DecorationRole:
            return c->model.decoration(*r, m_params);
        default:
            break;
        }
        return QVariant();
    }

    template <typename T, typename ... P>
    Delegate*       RowTableModel<T, P...>::delegate(create_k, int n)
    {
        Column* col = column(n);
        if(!col)
            return nullptr;
        if(col->delegate)
            return col->delegate;
        if(++(col->deltries) > 3)
            return nullptr;
        col->delegate   = col->model.delegate(m_params);        
        return col->delegate;
    }
    

    template <typename T, typename ... P>
    Delegate*       RowTableModel<T, P...>::delegate(int n)
    {
        Column* col = column(n);
        if(!col)
            return nullptr;
        return col->delegate;
    }

    template <typename T, typename ... P>
    const Delegate* RowTableModel<T, P...>::delegate(int n) const
    {
        const Column* col = column(n);
        if(!col)
            return nullptr;
        return col->delegate;
    }

    template <typename T, typename ... P>
    Qt::ItemFlags   RowTableModel<T, P...>::flags(const QModelIndex&idx) const 
    {
        return Qt::NoItemFlags;
    }

    template <typename T, typename ... P>
    bool RowTableModel<T, P...>::hasHorizontalHeader() const
    {
        return m_flags[F::HorizontalHeader];
    }
    
    template <typename T, typename ... P>
    bool RowTableModel<T, P...>::hasVerticalHeader() const
    {
        return m_flags[F::VerticalHeader];
    }


    template <typename T, typename ... P>
    QVariant    RowTableModel<T, P...>::headerData(int n, Qt::Orientation ori, int role) const 
    {
        if(role != Qt::DisplayRole) 
            return QVariant();

        switch(ori){
        case Qt::Horizontal:
            if(hasHorizontalHeader()){
                if(const Column* c = column(n))
                    return c->model.label;
            }
            break;
        case Qt::Vertical:
            if(std::get_if<rows_k>(&m_vHeader))
                return n+1;
            if(auto p = std::get_if<VariantFN>(&m_vHeader)){
                if(const T* r   = row(n)){
                    return verticalData(*p, *r, indices_gen<ARG_COUNT>());
                }
            }
            break;
        default:
            break;
        }
        return QVariant();
    }

    template <typename T, typename ... P>
    bool        RowTableModel<T, P...>::readOnly() const
    {
        return m_flags[F::ReadOnly];
    }


    template <typename T, typename ... P>
    T*          RowTableModel<T, P...>::row(int n) 
    {
        if((n >= 0) && (n < (int) m_rows.size()))
            return &m_rows[(size_t) n];
        return nullptr;
    }
    
    template <typename T, typename ... P>
    const T*      RowTableModel<T, P...>::row(int n) const
    {
        if((n >= 0) && (n < (int) m_rows.size()))
            return &m_rows[(size_t) n];
        return nullptr;
    }

    template <typename T, typename ... P>
    T*          RowTableModel<T, P...>::row(const QModelIndex& mi) 
    {
        return row(mi.row());
    }
    
    template <typename T, typename ... P>
    const T*      RowTableModel<T, P...>::row(const QModelIndex& mi) const
    {
        return row(mi.row());
    }

    template <typename T, typename ... P>
    int     RowTableModel<T, P...>::rowCount(const QModelIndex&) const 
    {
        return (int) m_rows.size();
    }

    template <typename T, typename ... P>
    bool    RowTableModel<T, P...>::setData(const QModelIndex& idx, const QVariant& var, int role) 
    {
        return false;
    }
    
    template <typename T, typename ... P>
    void    RowTableModel<T, P...>::setRows(const std::vector<T>& newData)
    {
        beginResetModel();
        m_rows  = newData;
        endResetModel();
    }
    
    template <typename T, typename ... P>
    void    RowTableModel<T, P...>::setRows(std::vector<T>&& newData)
    {
        beginResetModel();
        m_rows  = std::move(newData);
        endResetModel();
    }

    template <typename T, typename ... P>
    void    RowTableModel<T, P...>::showHorizontalHeader(bool v)
    {
        m_flags.set(F::HorizontalHeader, v);
    }

    template <typename T, typename ... P>
    void    RowTableModel<T, P...>::showVerticalHeader(bool v)
    {
        m_flags.set(F::VerticalHeader, v);
    }

    template <typename T, typename ... P>
    void 	        RowTableModel<T, P...>::sort(int colid, Qt::SortOrder order)
    {
        const Column* col = column(colid);
        if(!col)
            return ;
            
        if(col->model.fnCompare){
            auto sorter = [&](const T& a, const T& b) -> bool {
                Compare cmp = col->model.compare(a, b, m_params);
                return (order == Qt::AscendingOrder) ? (cmp == Compare::LESSER) : (cmp == Compare::GREATER);
            };

            std::stable_sort(m_rows.begin(), m_rows.end(), sorter);
        } else {
            Delegate*   del = delegate(CREATE, colid);
            auto sorter = [&](const T& a, const T& b) -> bool {
                QVariant    va  = col->model.sorter(a, m_params);
                QVariant    vb  = col->model.sorter(b, m_params);
                Compare cmp = del ? del->compare(va, vb) : yq::gluon::compare(va, vb);
                return (order == Qt::AscendingOrder) ? (cmp == Compare::LESSER) : (cmp == Compare::GREATER);
            };
            std::stable_sort(m_rows.begin(), m_rows.end(), sorter);
        }
        _changed();
    }

    template <typename T, typename ... P>
    void    RowTableModel<T, P...>::updateRows(const std::vector<T>& newData)
    {
        int     ac   = 0;
        int     rc   = 0;
        int     r0   = 0;
    
        for(auto& edit : diff::compare(m_rows, newData)){
            if(!edit.cnt)
                continue;
                
            switch(edit.type){
            case diff::Edit::Same:
                break;
            case diff::Edit::Add:
                r0  = edit.right.low+ac;
                beginInsertRows(QModelIndex(), r0, r0+edit.cnt );
                m_rows.insert(m_rows.begin()+r0, newData.begin()+edit.right.low, newData.begin()+edit.right.high);
                endInsertRows();
                rc += edit.cnt;
                break;
            case diff::Edit::Remove:
                r0  = edit.left.low+rc;
                beginRemoveRows(QModelIndex(), r0, r0+edit.cnt);
                m_rows.erase(m_rows.begin()+r0, m_rows.begin()+rc+edit.cnt);
                endRemoveRows();
                ac -= edit.cnt;
                break;
            }
        }
    }

    template <typename T, typename ... P>
        template <unsigned... Is>
    QVariant RowTableModel<T, P...>::verticalData(const VariantFN& fn, const T& val, indices<Is...>) const
    {
        return fn(val, std::get<Is, P...>(m_params)...);
    }
}
