////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsScene.hpp"
#include "GraphicsSceneInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsScene)

namespace yq::gluon {

    GraphicsSceneInfo::GraphicsSceneInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
    }
    
    GraphicsSceneInfo::~GraphicsSceneInfo()
    {
    }
    
    ///////////////////////////////////////////////////////////////////////////
    
    void GraphicsScene::init_info()
    {
        auto w = writer<GraphicsScene>();
        w.description("Graphics Scene");
    }

    GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent)
    {
    }
    
    GraphicsScene::GraphicsScene(const QRectF &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
    {
    }
    
    GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) : 
        QGraphicsScene(x,y,width,height,parent)
    {
    }
    
    GraphicsScene::~GraphicsScene()
    {
    }
}

#include "moc_GraphicsScene.cpp"
