////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsScene>
#include <gluon/core/ObjectQ.hpp>

namespace yq::gluon {
    class GraphicsSceneInfo : public ObjectQInfo {
    public:
        template <typename> class Writer;
        GraphicsSceneInfo(std::string_view zName, ObjectQInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~GraphicsSceneInfo();
    };

    //! More of a stub for now so common functionality can be added
    class GraphicsScene : public QGraphicsScene, public ObjectQ {
        YQ_OBJECT_INFO(GraphicsSceneInfo)
        YQ_OBJECTQ_DECLARE_ABSTRACT(GraphicsScene, ObjectQ)
        Q_OBJECT
    public:
    
        //! Test for printing to paper... (might be useful during rendering)
        static bool isPrinting();
    
        GraphicsScene(QObject *parent = nullptr);
        GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);
        GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
        ~GraphicsScene();
        
        static void init_info();
        
    private:
        static thread_local bool    s_printing;
    };
}
