////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/preamble.hpp>
#include <gluon/core/QtTypes.hpp>
#include <QMetaType>
#include <QVariant>
#include <0/basic/Any.hpp>
#include <0/meta/TypeInfo.hpp>

namespace yq::gluon {
    namespace {
        QVariant    a2q_string(const Any& v)
        {
            const std::string* s    = v.unsafe_ptr<std::string>();
            return qString(*s);
        }

        template <typename T>
        QVariant    a2q_type(const Any& v)
        {
            const T*    d   = v.unsafe_ptr<T>();
            return QVariant::fromValue(*d);
        }
        
        Any         q2a_string(const QVariant& v)
        {
            return Any(v.toString().toStdString());
        }
        
        template <typename T>
        Any         q2a_type(const QVariant& v)
        {
            return Any(v.value<T>());
        }

    }


    struct QtTypeRepo {
        std::unordered_map<int, QVariantToAnyFN>        q2a;
        std::unordered_map<Meta::id_t, AnyToQVariantFN> a2q;
        tbb::spin_rw_mutex                      mutex;
        
        template <typename T>
        void    add(QVariantToAnyFN fn)
        {
            q2a[qMetaTypeId<T>()]    = fn;
        }

        template <typename T>
        void    add(AnyToQVariantFN fn)
        {
            a2q[meta<T>().id()]    = fn;
        }
        
        template <typename T>
        void    add()
        {
            add<T>(q2a_type<T>);
            add<T>(a2q_type<T>);
        }
        
        QtTypeRepo()
        {
            add<QString>(q2a_string);
            add<std::string>(a2q_string);
            
            add<bool>();
            add<uint8_t>();
            add<uint16_t>();
            add<uint32_t>();
            add<uint64_t>();
            add<int8_t>();
            add<int16_t>();
            add<int32_t>();
            add<int64_t>();
            add<float>();
            add<double>();
        }
    };
    
    QtTypeRepo& qtTypeRepo()
    {
        static QtTypeRepo *s_ret = new QtTypeRepo;
        return *s_ret;
    }

    #define LOCK                                                    \
        QtTypeRepo& _r = qtTypeRepo();                              \
        tbb::spin_rw_mutex::scoped_lock _lock(_r.mutex, false);

    #define WLOCK                                                    \
        QtTypeRepo& _r = qtTypeRepo();                              \
        tbb::spin_rw_mutex::scoped_lock _lock(_r.mutex, true);

    std::string yString(const QString&s)
    {
        return s.toStdString();
    }

    QString     qString(std::string_view sv)
    {
        if(sv.empty())
            return QString();
        return QString::fromUtf8(sv.data(), sv.size());
    }
    
    QVariant    qVariant(const Any& v)
    {
        AnyToQVariantFN conv = nullptr;
        {
            LOCK
            auto j = _r.a2q.find(v.type().id());
            if(j != _r.a2q.end())
                conv    = j -> second;
        }
        if(!conv)
            return QVariant();
        return conv(v);
    }
    
    QVariant    qVariant(std::string_view sv)
    {
        return qString(sv);
    }
    
    QStringList         qStringList(std::span<const std::string> sp)
    {
        QStringList ret;
        ret.reserve(sp.size());
        for(const std::string& s : sp)
            ret << qString(s);
        return ret;
    }

    QStringList         qStringList(std::span<const std::string_view>sp)
    {
        QStringList ret;
        ret.reserve(sp.size());
        for(const std::string_view& s : sp)
            ret << qString(s);
        return ret;
    }
    

    Any         yAny(const QVariant&v)
    {
        QVariantToAnyFN     conv = nullptr;
        {
            LOCK
            auto j  = _r.q2a.find(v.userType());
            if(j != _r.q2a.end())
                conv    = j -> second;
        }
        if(!conv)
            return Any();
        return conv(v);
    }

    std::vector<std::string>    yStringVector(const QStringList&sl)
    {
        std::vector<std::string>    ret;
        ret.reserve(sl.size());
        for(const QString& s : sl)
            ret.push_back(yString(s));
        return ret;
    }
}
