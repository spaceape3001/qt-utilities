////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsLayer.hpp"
#include "GraphicsLayerInfoWriter.hpp"

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsLayer)

namespace yq::gluon {
    GraphicsLayerInfo::GraphicsLayerInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl) :
        ObjectInfo(zName, base, sl)
    {
    }
    
    GraphicsLayerInfo::~GraphicsLayerInfo()
    {
    }

    ///////////////////////////////////////////////////////////////////////////

    void GraphicsLayer::init_info()
    {
        auto w = writer<GraphicsLayer>();
        w.description("Graphics Layer");
        w.property("visibility", &GraphicsLayer::visibility).setter(&GraphicsLayer::setVisibility);
    }

    GraphicsLayer::GraphicsLayer(QObject*parent) : QObject(parent)
    {
    }
    
    GraphicsLayer::~GraphicsLayer()
    {
    }

    void    GraphicsLayer::draw(QPainter*, const QRectF&)
    {
    }

    GraphicsVisibility GraphicsLayer::effectiveVisibility() const
    {
        if(m_visibility != GraphicsVisibility::Auto)
            return m_visibility;
        GraphicsLayer*  par = parentLayer();
        if(par)
            return par -> effectiveVisibility();
        return GraphicsVisibility::Show;
    }

    GraphicsLayer* GraphicsLayer::parentLayer() const
    {
        return qobject_cast<GraphicsLayer*>(parent());
    }

    std::vector<GraphicsLayer*>   GraphicsLayer::sublayers() const
    {
        std::vector<GraphicsLayer*> ret;
        for(QObject* obj : children()){
            GraphicsLayer*  gl  = qobject_cast<GraphicsLayer*>(obj);
            if(gl)
                ret.push_back(gl);
        }
        return ret;
    }

    void        GraphicsLayer::setVisibility(GraphicsVisibility viz)
    {
        m_visibility    = viz;
        emit visibilityChanged(viz);
    }
}

#include "moc_GraphicsLayer.cpp"
