////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "WidgetQ.hpp"
#include "WidgetQInfoWriter.hpp"
#include <QWidget>

YQ_OBJECT_IMPLEMENT(yq::gluon::WidgetQ)

namespace yq::gluon {
    WidgetQInfo::WidgetQInfo(std::string_view zName, ObjectMeta& base, const std::source_location& sl) : 
        ObjectMeta(zName, base, sl)
    {
    }
    
    WidgetQInfo::~WidgetQInfo()
    {
    }

    void WidgetQ::init_meta()
    {
        auto w = writer<WidgetQ>();
        w.description("QWidget Wrapper");
    }

    WidgetQ::WidgetQ()
    {
    }
    
    WidgetQ::~WidgetQ()
    {
    }

    QWidget*    WidgetQ::qWidget()
    {
        return dynamic_cast<QWidget*>(this);
    }
    
    const QWidget*    WidgetQ::qWidget() const
    {
        return dynamic_cast<const QWidget*>(this);
    }
}

