////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsLayer.hpp"
#include "GraphicsLayerMetaWriter.hpp"

#include <gluon/graphics/GraphicsScene.hpp>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>

YQ_OBJECT_IMPLEMENT(yq::gluon::GraphicsLayer)

namespace yq::gluon {
    GraphicsLayerMeta::GraphicsLayerMeta(std::string_view zName, ObjectQMeta& base, const std::source_location& sl) :
        ObjectQMeta(zName, base, sl)
    {
    }
    
    GraphicsLayerMeta::~GraphicsLayerMeta()
    {
    }

    ///////////////////////////////////////////////////////////////////////////

    void GraphicsLayer::init_meta()
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

    void    GraphicsLayer::add_item(uint64_t i, QGraphicsItem* item)
    {
        if(!item)
            return;
        item->setData(ItemKey_Layer, (quint64) id());
        item->setData(ItemKey_Item, (quint64) i);
        m_items.insert({i,item});
        if(m_scene){
            switch(effectiveVisibility()){
            case GraphicsVisibility::Items:
                m_scene -> addItem(item);
                break;
            case GraphicsVisibility::Background:
            case GraphicsVisibility::Foreground:
                m_scene -> invalidate();
                break;
            default:
                break;
            }
        }
    }
    
    void    GraphicsLayer::add_items(uint64_t i, std::span<QGraphicsItem*> items)
    {
        for(QGraphicsItem* it : items)
            add_item(i,it);
    }
    
    void    GraphicsLayer::add_items(uint64_t i, std::initializer_list<QGraphicsItem*> items)
    {
        for(QGraphicsItem* it : items)
            add_item(i,it);
    }

    void    GraphicsLayer::delete_items(all_k)
    {
        if(m_scene && (effectiveVisibility() == GraphicsVisibility::Items)){
            for(auto& itr : m_items){
                // TODO
            }
        }
        m_items.clear();
    }
    
    void    GraphicsLayer::delete_items(uint64_t)
    {
        // TODO
    }

    void    GraphicsLayer::draw(QPainter* painter, const QRectF& area)
    {
        if(!painter)
            return ;
            
        QStyleOptionGraphicsItem options;
        options.exposedRect = area;

        for(auto& itr : m_items){
            if(!itr.second)
                continue;
            itr.second->paint(painter, &options, nullptr);
        }
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
        if(viz != m_visibility){
            GraphicsVisibility old = m_visibility;
            m_visibility    = viz;
            emit visibilityChanged(viz, old);
        }
    }
}

#include "moc_GraphicsLayer.cpp"
