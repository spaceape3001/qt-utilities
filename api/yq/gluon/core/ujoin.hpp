////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QString>
#include <type_traits>
#include <yq/trait/always_false.hpp>

namespace yq {
    /*! Joins a collection into a separator (no separator)
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    QString     joinQString(const Tmpl<T...>& collection)
    {
        QString    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, QString>;
        
        if constexpr ( is_string ){
            int  n   = 0;
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        for(const auto&s : collection){
            if constexpr (is_string) {
                ret += s;
            } else {
                static_assert(yq::always_false_v<value_t>, "Argument deduction failed");
            }
        }
        return ret;
    }


    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    QString     joinQString(const Tmpl<T...>& collection, const QString& separator)
    {
        QString    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, QString>;
        
        if constexpr ( is_string ){
            int  n   = collection.size() * separator.size();
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        bool    f   = true;
        for(const auto&s : collection){
            if(f){
                f   = false;
            } else {
                ret += separator;
            }
            
            if constexpr (is_string) {
                ret += s;
            } else {
                static_assert(yq::always_false_v<value_t>, "Argument deduction failed");
            }
        }
        return ret;
    }
    
    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    QString     joinQString(const Tmpl<T...>& collection, QChar separator)
    {
        QString    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, QString>;
        
        if constexpr ( is_string ){
            int  n   = collection.size();
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        bool    f   = true;
        for(const auto&s : collection){
            if(f){
                f   = false;
            } else {
                ret += separator;
            }
            
            if constexpr (is_string) {
                ret += s;
            } else {
                static_assert(yq::always_false_v<value_t>, "Argument deduction failed");
            }
        }
        return ret;
    }
    
}
