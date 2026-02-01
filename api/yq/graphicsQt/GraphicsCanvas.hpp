////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/core/Flags.hpp>
#include <yq/gluon/app/SubWindow.hpp>
#include <yq/typedef/meta_id.hpp>

class QGraphicsItem;

namespace yq::gluon {
    class GraphicsScene;
    class GraphicsView;
    class GraphicsTool;
    class GraphicsToolMeta;
    
    class GraphicsCanvas : public SubWindow {
        Q_OBJECT
    public:

        enum class Feature : uint8_t {
            SelectEffect
            // some go here....
        };
        
    
        GraphicsCanvas(QWidget*parent=nullptr);
        GraphicsCanvas(GraphicsScene*, QWidget*parent=nullptr);
        GraphicsCanvas(GraphicsView*, QWidget*parent=nullptr);
        ~GraphicsCanvas();

        bool            feature(Feature) const;
        void            featureEnable(Feature);
        void            featureDisable(Feature);
        Flags<Feature>  features() const { return m_features; }
        
        bool                    hasSelectEffect() const;
        
        void                    setEdgePen(QPen);
        void                    setPaperBrush(QBrush);
        void                    setBackgroundBrush(QBrush);

        GraphicsScene*          scene() { return m_scene; }
        const GraphicsScene*    scene() const { return m_scene; }
        
        GraphicsView*           view() { return m_view; }
        const GraphicsView*     view() const { return m_view; }
        
        uint64_t                currentTool() const;
        
        //! "Selects" a specific item, does NOT affect other items
        void    select(QGraphicsItem*);
        
        //! Deselects a specific item, does not affect  other items
        void    deselect(QGraphicsItem*);


        void    selectThis(QGraphicsItem*);
        void    selectThese(const std::vector<QGraphicsItem*>&);
        void    selectThese(const QList<QGraphicsItem*>&);

        auto&   selected() const { return m_selected; }
        
    protected:
        //! Selection effect
        virtual QGraphicsEffect*    selectEffect(QGraphicsItem*);
    
    public slots:
        void            selectAll();
        void            selectNone();
        
    signals:
        void        toolChanged(uint64_t);
        
    public slots:
        void        setTool(uint64_t);

    private:
        GraphicsScene* const    m_scene;
        GraphicsView* const     m_view;
        Flags<Feature>          m_features;
        
        std::map<meta_id_t, GraphicsTool*>      m_tools;
        std::vector<QGraphicsItem*>             m_selected;
        
    };
}
