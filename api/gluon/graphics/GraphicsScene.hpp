////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsScene>
#include <gluon/core/ObjectQ.hpp>
#include <yq/core/Flags.hpp>

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

        enum class AutoDraw : uint8_t {
            SceneRect,
            USER            //! Use this for extending....
        };
        
        static constexpr const AutoDraw     AutoDraw_SceneRect              = AutoDraw::SceneRect;
    
        //! Test for printing to paper... (might be useful during rendering)
        static bool isPrinting();
    
        GraphicsScene(QObject *parent = nullptr);
        GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);
        GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
        ~GraphicsScene();
        
        static void init_meta();
        
        Flags<AutoDraw> autoDraw() const;
        bool            autoDraw(AutoDraw) const;

        void            autoDrawEnable(AutoDraw);
        void            autoDrawDisable(AutoDraw);
        
        //  Generic draw
        void            draw(QPainter*, const QRectF& rect={});
        
        QPen            sceneRectPen() const;
        QBrush          sceneRectBrush() const;

        void            setSceneRectPen(QPen);
        void            setSceneRectBrush(QBrush);

        void            print(QPainter*, const QRectF& rect={});

    protected:
        void            drawBackground(QPainter*, const QRectF&rect={}) override;
        void            drawItems(QPainter*, const QRectF&rect={});
        void            drawForeground(QPainter*, const QRectF&rect={}) override;
        void            drawSceneRect(QPainter*, const QRectF&rect={});

    private:
        static thread_local bool    s_printing;

        Flags<AutoDraw>         m_autoDraw;
        QBrush                  m_sceneRectBrush;
        QPen                    m_sceneRectPen;

    };
}
