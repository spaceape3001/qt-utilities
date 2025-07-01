////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>

class QObject;

namespace yq::gluon {
    class ObjectQ;

    template <typename> class ObjectQFixer;

    class ObjectQInfo : public ObjectInfo {
    public:
        template <typename> class Writer;
        
        using ObjectInfo::create;
        virtual ObjectQ*    create(QObject*) const = 0;

        ObjectQInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~ObjectQInfo();
    };
    
    #define YQ_OBJECTQ_DECLARE_ABSTRACT(cls, base)          \
        YQ_OBJECT_DECLARE(cls, base)                        \
        static constexpr const bool kAbstract   = true;
        
    #define YQ_OBJECTQ_DECLARE(cls, base)                   \
        YQ_OBJECT_DECLARE(cls, base)                        \
        friend class ::yq::gluon::ObjectQFixer<cls>         \
        static constexpr const bool kAbstract   = false;
    
    /*! \brief Wrapper for QObject based meta to leverage
    
        \note This is not a QObject itself, but meant to be derived from a QObject 
        based class so that it can leverage the quill's object meta system too
        
        \note QWidget should use WidgetQ helper
    */
    class ObjectQ : public Object {
        YQ_OBJECT_FIXER(ObjectQFixer)
        YQ_OBJECT_INFO(ObjectQInfo)
        YQ_OBJECT_DECLARE(ObjectQ, Object)
    public:
        static void init_meta();
        static constexpr const bool kAbstract   = true;
        
        QObject*            qObject();
        const QObject*      qObject() const;
        
    protected:
        ObjectQ();
        virtual ~ObjectQ();
    };
}
