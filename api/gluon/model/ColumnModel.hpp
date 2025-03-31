////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QVariant>
#include <functional>
#include <memory>
#include <yq/core/Flags.hpp>
#include <yq/keywords.hpp>
#include <yq/core/Compare.hpp>
#include <yq/trait/indices.hpp>

namespace yq::gluon {
    enum class ColOption : uint8_t {
        Set,
        Add,
        Icon
    };
    
    class Delegate;
    
    using ColOptions   = Flags<ColOption>;

    template <typename T, typename ... P>
    class ColumnModel {
    public:

        static constexpr const size_t   ARG_COUNT   = sizeof...(P);
    
        using VariantFN     = std::function<QVariant(const T&, P ... args)>;
        using AddFN         = std::function<T(P ... args, const QVariant&)>;
        using SetFN         = std::function<std::error_code(const T&, P ... args, const QVariant&)>;
        using DropIdFN      = std::function<std::error_code(const T&, P ... args, std::span<const T>)>;
        using DropFN        = std::function<std::error_code(const T&, P ... args, const QVariant&)>;
        using MimeListFN    = std::function<QStringList(const T&, P ... args)>;
        using DelegateFN    = std::function<Delegate*(P ... args)>;
        using CompareFN     = std::function<Compare(const T&,const T&,P ... args)>;
        //using CreateFN      = std::function<SCPtr(ColOptions)>;
        
        using param_t       = std::tuple<P...>;
        
        AddFN           fnAdd;              //!< Call if column is add-aware
        VariantFN       fnDecoration;       //!< Decoration data
        VariantFN       fnDisplay;          //!< Display data (mandatory)
        DelegateFN      fnDelegate;         //!< Delegate creator (can be non-existent)
        DropIdFN        fnDropId;           //!< Drop Id data here
        DropFN          fnDrop;             //!< Drop other data here
        MimeListFN      fnDropMime;         //!< Type of mimes allowed
        VariantFN       fnEdit;             //!< Edit data expected
        SetFN           fnSet;              //!< May work
        VariantFN       fnSort;             //!< Overrides display
        CompareFN       fnCompare;          //!< Comparison of two things, overrides fnSort

        QVariant        addMsg;             //!< Add message
        QVariant        label;              //!< Header label
        QVariant        defVal;             //!< Value if the ID is bad
        unsigned int    number  = 0;        //!< Column number, tracked by IdModel
        int             qtType  = 0;        //!< Qt data type

        ColumnModel();
        ~ColumnModel();
        
        static void                 reg_column(const std::string&, const ColumnModel&);
        static void                 reg_column(default_k, const std::string&, const ColumnModel&);
        static const ColumnModel*   lookup(const std::string&);
        
        Compare         compare(const T&, const T&, const param_t&) const;
        QVariant        decoration(const T&, const param_t&) const;
        Delegate*       delegate(const param_t&) const;
        QVariant        display(const T&, const param_t&) const;
        QVariant        edit(const T&, const param_t&) const;
        QVariant        sorter(const T&, const param_t&) const;

    private:
        template <unsigned... Is>
        Compare         compare(const T&, const T&, const param_t&, indices<Is...> vals) const;

        template <unsigned... Is>
        QVariant        decoration(const T&, const param_t&, indices<Is...> vals) const;

        template <unsigned... Is>
        Delegate*       delegate(const param_t&, indices<Is...> vals) const;

        template <unsigned... Is>
        QVariant        display(const T&, const param_t&, indices<Is...>) const;

        template <unsigned... Is>
        QVariant        edit(const T&, const param_t&, indices<Is...> vals) const;

        template <unsigned... Is>
        QVariant        sorter(const T&, const param_t&, indices<Is...> vals) const;

        struct Repo;
        static Repo&    repo();
    };
}

