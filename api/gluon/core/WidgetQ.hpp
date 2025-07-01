////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Object.hpp>

class QWidget;

namespace yq::gluon {
    class WidgetQ;

    template <typename> class WidgetQFixer;

    class WidgetQInfo : public ObjectMeta {
    public:
        template <typename> class Writer;
        
        using ObjectMeta::create;
        virtual WidgetQ*    create(QWidget*) const = 0;

        WidgetQInfo(std::string_view zName, ObjectMeta& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~WidgetQInfo();
    };
    
    #define YQ_WIDGETQ_DECLARE_ABSTRACT(cls, base)          \
        YQ_OBJECT_DECLARE(cls, base)                        \
        static constexpr const bool kAbstract   = true;
        
    #define YQ_WIDGETQ_DECLARE(cls, base)                   \
        YQ_OBJECT_DECLARE(cls, base)                        \
        friend class ::yq::gluon::WidgetQFixer<cls>         \
        static constexpr const bool kAbstract   = false;
    
    /*! \brief Wrapper for QWidget based meta to leverage
    
        \note This is not a QWidget itself, but meant to be derived from a QWidget 
        based class so that it can leverage the quill's object meta system too
        
        \note QWidget should use WidgetQ helper
    */
    class WidgetQ : public Object {
        YQ_OBJECT_FIXER(WidgetQFixer)
        YQ_OBJECT_INFO(WidgetQInfo)
        YQ_OBJECT_DECLARE(WidgetQ, Object)
    public:
        static void init_meta();
        static constexpr const bool kAbstract   = true;
        
        QWidget*            qWidget();
        const QWidget*      qWidget() const;
        
    protected:
        WidgetQ();
        virtual ~WidgetQ();
    };
}
