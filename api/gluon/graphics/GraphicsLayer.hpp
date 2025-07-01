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
#include <gluon/core/ObjectQ.hpp>
#include <yq/core/UniqueID.hpp>
#include <gluon/keywords.hpp>

class QGraphicsItem;
class QPainter;
class QRectF;

#define YQ_LAYER_DECLARE(cls, base)             YQ_OBJECTQ_DECLARE(cls, base)

namespace yq::gluon {
    class GraphicsScene;
    
    class GraphicsLayerInfo : public ObjectQInfo {
    public:
        template <typename> class Writer;
        GraphicsLayerInfo(std::string_view zName, ObjectQInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        ~GraphicsLayerInfo();
    };
    
    /*! \brief Collection of graphics items
    */
    class GraphicsLayer : public QObject, public ObjectQ, public UniqueID {
        YQ_OBJECT_INFO(GraphicsLayerInfo)
        YQ_OBJECTQ_DECLARE_ABSTRACT(GraphicsLayer, ObjectQ)
        Q_OBJECT
        Q_PROPERTY(GraphicsVisibility visibility MEMBER m_visibility WRITE setVisibility)
    public:
    
        enum {
            ItemKey_Layer       = 0,
            ItemKey_Item        = 1
        };
    
        using item_map_t                = std::multimap<uint64_t, QGraphicsItem*>;
        using item_pair_t               = item_map_t::value_type;
        using item_const_iterator_t     = item_map_t::const_iterator;
    
        GraphicsLayer(QObject*parent=nullptr);
        ~GraphicsLayer();
        
        virtual void    draw(QPainter*, const QRectF&);
        
        //! Returns our effective visibility
        GraphicsVisibility              effectiveVisibility() const;
        
        std::vector<GraphicsLayer*>     sublayers() const;
        
        GraphicsLayer*                  parentLayer() const;

        //! Returns *OUR* visibility (which ignores parent)
        GraphicsVisibility              visibility() const { return m_visibility; }
        
        static void init_meta();
        
        void        add_item(uint64_t, QGraphicsItem*);
        void        add_items(uint64_t, std::span<QGraphicsItem*>);
        void        add_items(uint64_t, std::initializer_list<QGraphicsItem*>);
        
        template <typename Pred>
        auto        for_items(uint64_t, Pred&&);
        
        void        delete_items(uint64_t);
        void        delete_items(all_k);
        
    signals:
        void        visibilityChanged(GraphicsVisibility newVisibility, GraphicsVisibility oldVisibility);
        
    public slots:
        void        setVisibility(GraphicsVisibility);
        
    private:
        friend class GraphicsScene;
        
        GraphicsScene*          m_scene         = nullptr;
        item_map_t              m_items;
        GraphicsVisibility      m_visibility    = GraphicsVisibility::Auto;
    };
}
