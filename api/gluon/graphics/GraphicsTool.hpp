////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <yq/core/UniqueID.hpp>
#include <gluon/core/ObjectQ.hpp>

class QIcon;
class QCursor;

namespace yq::gluon {
    class GraphicsToolInfo : public ObjectQInfo {
    public:
        template <typename> class Writer;
        GraphicsToolInfo(std::string_view zName, ObjectQInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~GraphicsToolInfo();
    };

    class GraphicsTool : public QObject, public ObjectQ, public UniqueID {
        YQ_OBJECT_INFO(GraphicsToolInfo)
        YQ_OBJECTQ_DECLARE_ABSTRACT(GraphicsTool, ObjectQ)
        Q_OBJECT
    public:
        
        static void init_info();
        
        virtual QCursor cursor() const;
        virtual QIcon   icon() const;
        
    signals:
        void        cursorChanged(const QCursor&);
        void        iconChanged(const QIcon&);
        
    protected:
        GraphicsTool();
        ~GraphicsTool();
    };
}
