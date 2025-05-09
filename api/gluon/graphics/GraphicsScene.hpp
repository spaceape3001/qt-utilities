////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsScene>
#include <yq/core/Object.hpp>

namespace yq::gluon {
    class GraphicsSceneInfo : public ObjectInfo {
    public:
        template <typename> class Writer;
        GraphicsSceneInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~GraphicsSceneInfo();
    };

    //! More of a stub for now so common functionality can be added
    class GraphicsScene : public QGraphicsScene, public Object {
        YQ_OBJECT_INFO(GraphicsSceneInfo)
        YQ_OBJECT_DECLARE(GraphicsScene, Object)
        Q_OBJECT
    public:
        GraphicsScene(QObject *parent = nullptr);
        GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);
        GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
        ~GraphicsScene();
        
        static void init_info();
    };
}
