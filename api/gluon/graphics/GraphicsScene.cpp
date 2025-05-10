////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsScene.hpp"
#include "GraphicsSceneInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsScene)

namespace yq::gluon {

    GraphicsSceneInfo::GraphicsSceneInfo(std::string_view zName, ObjectQInfo& base, const std::source_location& sl) :
        ObjectQInfo(zName, base, sl)
    {
    }
    
    GraphicsSceneInfo::~GraphicsSceneInfo()
    {
    }
    
    ///////////////////////////////////////////////////////////////////////////
    
    thread_local bool    GraphicsScene::s_printing = false;

    void GraphicsScene::init_info()
    {
        auto w = writer<GraphicsScene>();
        w.description("Graphics Scene");
    }

    bool GraphicsScene::isPrinting()
    {
        return s_printing;
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
