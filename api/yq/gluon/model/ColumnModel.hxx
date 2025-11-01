////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/model/ColumnModel.hpp>
#include <yq/text/IgCase.hpp>
#include <map>

namespace yq::gluon {
    template <typename T, typename ... P>
    struct ColumnModel<T,P...>::Repo {
        std::map<std::string,ColumnModel,IgCase>    columns;
        std::vector<std::string>                    defcols;
    };
    
    template <typename T, typename ... P>
    ColumnModel<T,P...>::Repo& ColumnModel<T,P...>::repo()
    {
        static Repo s_repo;
        return s_repo;
    }

    template <typename T, typename ... P>
    void                 ColumnModel<T,P...>::reg_column(const std::string& k, const ColumnModel& mdl)
    {
        auto& _r = repo();
        _r.columns[k]   = mdl;
    }

    template <typename T, typename ... P>
    void                 ColumnModel<T,P...>::reg_column(default_k, const std::string& k, const ColumnModel& mdl)
    {
        auto& _r = repo();
        _r.columns[k]   = mdl;
        _r.defcols.push_back(k);
    }

    template <typename T, typename ... P>
    const ColumnModel<T,P...>*   ColumnModel<T,P...>::lookup(const std::string&k)
    {
        auto& _r = repo();
        auto i = _r.columns.find(k);
        if(i!=_r.columns.end())
            return &i->second;
        return nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////

    template <typename T, typename ... P>
    ColumnModel<T,P...>::ColumnModel()
    {
    }
    
    template <typename T, typename ... P>
    ColumnModel<T,P...>::~ColumnModel()
    {
    }

    template <typename T, typename ... P>
        template <unsigned... Is>
    Compare         ColumnModel<T,P...>::compare(const T&a, const T&b, const param_t&params, indices<Is...>) const
    {
        if(!fnCompare)
            return Compare::UNCOMPARABLE;
        return fnCompare(a,b,std::get<Is, P...>(params)...);
    }

    template <typename T, typename ... P>
    Compare         ColumnModel<T,P...>::compare(const T&a, const T&b, const param_t&params) const
    {
        return compare(a,b,params,indices_gen<ARG_COUNT>());
    }

    template <typename T, typename ... P>
        template <unsigned... Is>
    QVariant        ColumnModel<T,P...>::decoration(const T&val, const param_t&params, indices<Is...>) const
    {
        if(!fnDecoration)
            return QVariant();
        return fnDecoration(val, std::get<Is, P...>(params)...);
    }

    template <typename T, typename ... P>
    QVariant        ColumnModel<T,P...>::decoration(const T&val, const param_t&params) const
    {
        return decoration(val, params, indices_gen<ARG_COUNT>());
    }

    template <typename T, typename ... P>
        template <unsigned... Is>
    Delegate*       ColumnModel<T,P...>::delegate(const param_t&params, indices<Is...>) const
    {
        if(!fnDelegate)
            return nullptr;
        return fnDelegate(std::get<Is, P...>(params)...);
    }

    template <typename T, typename ... P>
    Delegate*       ColumnModel<T,P...>::delegate(const param_t&params) const
    {
        return delegate(params, indices_gen<ARG_COUNT>());
    }


    template <typename T, typename ... P>
        template <unsigned... Is>
    QVariant        ColumnModel<T,P...>::display(const T&val, const param_t&params, indices<Is...>) const
    {
        if(!fnDisplay)
            return {};
        return fnDisplay(val, std::get<Is, P...>(params)...);
    }

    template <typename T, typename ... P>
    QVariant        ColumnModel<T,P...>::display(const T&val, const param_t&params) const
    {
        return display(val, params, indices_gen<ARG_COUNT>());
    }

    template <typename T, typename ... P>
        template <unsigned... Is>
    QVariant        ColumnModel<T,P...>::edit(const T&val, const param_t&params, indices<Is...>) const
    {
        if(fnEdit)
            return fnEdit(val, std::get<Is, P...>(params)...);
        if(fnDisplay)
            return fnDisplay(val, std::get<Is, P...>(params)...);
        return QVariant();
    }

    template <typename T, typename ... P>
    QVariant        ColumnModel<T,P...>::edit(const T&val, const param_t&params) const
    {
        return edit(val, params, indices_gen<ARG_COUNT>());
    }

    template <typename T, typename ... P>
        template <unsigned... Is>
    QVariant        ColumnModel<T,P...>::sorter(const T&val, const param_t&params, indices<Is...>) const
    {
        if(fnSort)
            return fnSort(val, std::get<Is, P...>(params)...);
        if(fnDisplay)
            return fnDisplay(val, std::get<Is, P...>(params)...);
        return QVariant();
    }

    template <typename T, typename ... P>
    QVariant        ColumnModel<T,P...>::sorter(const T&val, const param_t&params) const
    {
        return sorter(val, params, indices_gen<ARG_COUNT>());
    }
}


