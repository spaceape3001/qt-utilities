////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <yq/core/Object.hpp>
#include <gluon/core/RefQ.hpp>

namespace yq::gluon {
    class GraphicsToolInfo : public ObjectInfo {
    public:
        template <typename> class Writer;
        GraphicsToolInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~GraphicsToolInfo();
    };

    class GraphicsTool : public QObject, public Object, public RefQ {
        YQ_OBJECT_INFO(GraphicsToolInfo)
        YQ_OBJECT_DECLARE(GraphicsTool, Object)
        Q_OBJECT
    public:
        
        static void init_info();
        
    protected:
        GraphicsTool();
        ~GraphicsTool();
    };
}
