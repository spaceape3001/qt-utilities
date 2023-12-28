////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/preamble.hpp>
#include <0/basic/Compare.hpp>
#include <QString>
#include <QList>
#include <0/trait/always_false.hpp>

class QIcon;
class QObject;

namespace log4cpp { class CategoryStream; }

namespace yq::gluon {
    Compare     compare(const QByteArray&, const QByteArray&);
    Compare     compare(const QString&, const QString&);
    Compare     compare(const QVariant&, const QVariant&);

    Compare     compare_igCase(const QByteArray& a, const QByteArray& b);
    Compare     compare_igCase(const QString& a, const QString& b);
    
    Compare     compare_igCase(const QVariant&, const QVariant&);

    bool    is_similar(const QString&, const QString&);
    bool    is_similar(const QByteArray&, const QByteArray&);

    std::vector<const QObject*>   qobjectLineage(const QObject*, bool fIncSelf=false);
    
    QStringList         qStringList(std::span<const std::string>);
    QStringList         qStringList(std::span<const std::string_view>);
    
    std::vector<std::string>    yStringVector(const QStringList&);

    /*!
        Gets an icon from a filename.  Any %1 notation will be replaced by 
        common icon sizes and tested.
        
        \note Qt restriction requires this to run on the MAIN THREAD.  Any
        other thread will simply return an empty icon
    */
    QIcon       fetchIcon(const QString&);

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
    
    template <typename T>
    std::vector<const T*>  toCVector(const QList<T*>& list)
    {
        return std::vector<const T*>(list.begin(), list.end());
    }

    template <typename T>
    std::vector<T>  toVector(const QList<T>& list)
    {
        return std::vector<T>(list.begin(), list.end());
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
    

    void    logAllResources();
    void    logAllResources(log4cpp::CategoryStream&&);
}

