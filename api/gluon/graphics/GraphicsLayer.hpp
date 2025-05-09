////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <map>
#include <span>

#include <gluon/graphics/GraphicsVisibility.hpp>
#include <yq/core/Object.hpp>

class QGraphicsItem;
class QPainter;
class QRectF;

namespace yq::gluon {
    class GraphicsItem;
    
    class GraphicsLayerInfo : public ObjectInfo {
    public:
        template <typename> class Writer;
        GraphicsLayerInfo(std::string_view zName, ObjectInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~GraphicsLayerInfo();
    };
    

    /*! \brief Collection of graphics items
    */
    class GraphicsLayer : public QObject, public Object {
        YQ_OBJECT_INFO(GraphicsLayerInfo)
        YQ_OBJECT_DECLARE(GraphicsLayer, Object)
        Q_OBJECT
        Q_PROPERTY(GraphicsVisibility visibility MEMBER m_visibility WRITE setVisibility)
    public:
    
        using item_map_t    = std::multimap<uint64_t, QGraphicsItem*>;
        using item_pair_t   = item_map_t::value_type;
    
        GraphicsLayer(QObject*parent=nullptr);
        ~GraphicsLayer();
        
        virtual void    draw(QPainter*, const QRectF&);
        
        //! Returns our effective visibility
        GraphicsVisibility              effectiveVisibility() const;
        
        std::vector<GraphicsLayer*>     sublayers() const;
        
        GraphicsLayer*                  parentLayer() const;

        //! Returns *OUR* visibility (which ignores parent)
        GraphicsVisibility              visibility() const { return m_visibility; }
        
        static void init_info();
        
        
    signals:
        void        visibilityChanged(GraphicsVisibility);
        
    public slots:
        void        setVisibility(GraphicsVisibility);
        
    private:
        item_map_t              m_items;
        GraphicsVisibility      m_visibility = GraphicsVisibility::Auto;
    };
}
