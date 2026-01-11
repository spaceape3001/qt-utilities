////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsScene>
#include <yq/core/Flags.hpp>

namespace yq { class ObjectMeta; }

namespace yq::gluon {
  
    //! More of a stub for now so common functionality can be added
    class GraphicsScene : public QGraphicsScene {
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

        virtual const ObjectMeta*   my_meta() const { return nullptr; }

        // IF We need meta, it'll be done otherwise.... (maybe virtuals here...)
        
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
