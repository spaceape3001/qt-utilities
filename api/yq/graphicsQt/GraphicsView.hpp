////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QBrush>
#include <QGraphicsView>
#include <QPen>

#include <yq/core/Flags.hpp>

namespace yq { class ObjectMeta; }

namespace yq::gluon {
    class GraphicsScene;
    class GraphicsTool;
    
    /*! \brief Enhanced GraphicsView
    */
    class GraphicsView : public QGraphicsView {
        Q_OBJECT
    public:
    
        enum class Feature : uint8_t {
            MaxViewport,        //! Use the max primary monitor for viewport size hint
            MouseWheelRotate,
            MouseWheelZoom,     //! Enable mouse wheel for zooming
            USER                //! Use this for extending...
        };
        
        static constexpr const Feature      Feature_MaxViewport             = Feature::MaxViewport;
        static constexpr const Feature      Feature_MouseWheelRotate        = Feature::MouseWheelRotate;
        static constexpr const Feature      Feature_MouseWheelZoom          = Feature::MouseWheelZoom;
    
    
        //! Steps to double zoom
        static constexpr const unsigned kDOUBLE = 8;    // eight steps to double
        static constexpr const double   kROTATE = 2.5;

        //! Once needed, use this....
        virtual const ObjectMeta*   my_meta() const { return nullptr; }
    
        //! Constructor
        GraphicsView(GraphicsScene*, QWidget*parent=nullptr);
        
        //! Destructor
        ~GraphicsView();
        
        Flags<Feature>  features() const;
        bool            feature(Feature) const;
        void            featureEnable(Feature);
        void            featureDisable(Feature);

        bool            featureMouseWheelRotate() const;
        bool            featureMouseWheelZoom() const;

        using QGraphicsView::mapToScene;
        QPointF         mapToScene(const QPointF&) const;

        void            setMouseWheelZoomModifiers(Qt::KeyboardModifiers);
        void            setMouseWheelRotateModifiers(Qt::KeyboardModifiers);
        
        void            setTool(GraphicsTool*);
        
        QSize           sizeHint() const override;

        //! Zoom factor
        double          zoomFactor() const;
        
        GraphicsTool*   tool() const;
        

        // tool helpers....
        
        bool            isWheelRotate(QWheelEvent*) const;
        bool            isWheelZoom(QWheelEvent*) const;
        
        void            invalidateForeground();

        void            thWheelRotate(QWheelEvent*);
        void            thWheelZoom(QWheelEvent*);
        
        using QGraphicsView::setBackgroundBrush;
        
        GraphicsScene*          scene()  { return m_scene; }
        const GraphicsScene*    scene() const { return m_scene; }

    public slots:
        //! Adjusts the zoom to fit the scene
        void            fitToScene();
        
        //! Zooms in one step
        void            zoomIn();

        //! Zooms out one step
        void            zoomOut();
        
        void            zoomBy(double);
        
        //! Sets the zoom factor
        void            setZoomFactor(double);
        
        void            translateBy(const QPointF&);
        
    signals:
        //! Advertises the current mouse position in the view
        void            mouseAt(double, double);
        
        void            zoomChanged(double);
        
        void            viewportResized();
        void            resized();
    
    protected:

        void 	        contextMenuEvent(QContextMenuEvent*) override;
        void 	        dragEnterEvent(QDragEnterEvent*) override;
        void 	        dragLeaveEvent(QDragLeaveEvent*) override;
        void 	        dragMoveEvent(QDragMoveEvent*) override;
        void 	        drawBackground(QPainter*, const QRectF &) override;
        void 	        drawForeground(QPainter*, const QRectF &) override;
        void 	        dropEvent(QDropEvent*) override;
        void 	        enterEvent(QEnterEvent*) override;
        void 	        focusInEvent(QFocusEvent*) override;
        void 	        focusOutEvent(QFocusEvent*) override;
        void 	        keyPressEvent(QKeyEvent*) override;
        void 	        keyReleaseEvent(QKeyEvent*) override;
        void 	        leaveEvent(QEvent*) override;
        void            mouseDoubleClickEvent(QMouseEvent*) override;
        void            mouseMoveEvent(QMouseEvent*) override;
        void            mousePressEvent(QMouseEvent*) override;
        void            mouseReleaseEvent(QMouseEvent*) override;
        void            resizeEvent(QResizeEvent*) override;
        void 	        tabletEvent(QTabletEvent*) override;
        bool            viewportEvent(QEvent*) override;
        void            wheelEvent(QWheelEvent*) override;
        

    private:
        GraphicsScene* const    m_scene;
    
        Flags<Feature>          m_features;
        Qt::KeyboardModifiers   m_mouseWheelZoomModifiers = {};
        Qt::KeyboardModifiers   m_mouseWheelRotateModifiers = {};
        GraphicsTool*           m_tool          = nullptr;
    };
}
