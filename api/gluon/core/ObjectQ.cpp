////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "ObjectQ.hpp"
#include "ObjectQMetaWriter.hpp"
#include <QObject>

YQ_OBJECT_IMPLEMENT(yq::gluon::ObjectQ)

namespace yq::gluon {
    ObjectQMeta::ObjectQMeta(std::string_view zName, ObjectMeta& base, const std::source_location& sl) : 
        ObjectMeta(zName, base, sl)
    {
    }
    
    ObjectQMeta::~ObjectQMeta()
    {
    }

    void ObjectQ::init_meta()
    {
        auto w = writer<ObjectQ>();
        w.description("QObject Wrapper");
    }

    ObjectQ::ObjectQ()
    {
    }
    
    ObjectQ::~ObjectQ()
    {
    }

    QObject*    ObjectQ::qObject()
    {
        return dynamic_cast<QObject*>(this);
    }
    
    const QObject*    ObjectQ::qObject() const
    {
        return dynamic_cast<const QObject*>(this);
    }
}

