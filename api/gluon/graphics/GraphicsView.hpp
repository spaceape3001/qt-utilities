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
#include <yq/core/Object.hpp>
#include <gluon/core/WidgetQ.hpp>

namespace yq::gluon {
    class GraphicsScene;
    class GraphicsTool;
    
    class GraphicsViewInfo : public WidgetQInfo {
    public:
        template <typename> class Writer;
        GraphicsViewInfo(std::string_view zName, WidgetQInfo& base, const std::source_location& sl=std::source_location::current());
    protected:
        virtual ~GraphicsViewInfo();
    };
    
    /*! \brief Enhanced GraphicsView
    */
    class GraphicsView : public QGraphicsView, public WidgetQ {
        YQ_OBJECT_INFO(GraphicsViewInfo)
        YQ_WIDGETQ_DECLARE_ABSTRACT(GraphicsView, WidgetQ)
        Q_OBJECT
    public:
    
        enum class AutoDraw : uint8_t {
            SceneRect,
            USER            //! Use this for extending....
        };
        
        static constexpr const AutoDraw     AutoDraw_SceneRect              = AutoDraw::SceneRect;
        
        enum class Feature : uint8_t {
            MaxViewport,        //! Use the max primary monitor for viewport size hint
            MouseWheelZoom,     //! Enable mouse wheel for zooming
            USER                //! Use this for extending...
        };
        
        static constexpr const Feature      Feature_MaxViewport             = Feature::MaxViewport;
        static constexpr const Feature      Feature_MouseWheelZoom          = Feature::MouseWheelZoom;
    
    
        //! Steps to double zoom
        static constexpr const unsigned kDOUBLE = 8;    // eight steps to double
        
        static void init_info();
    
        //! Constructor
        GraphicsView(GraphicsScene*, QWidget*parent=nullptr);
        
        //! Destructor
        ~GraphicsView();
        
        Flags<AutoDraw> autoDraw() const;
        bool            autoDraw(AutoDraw) const;

        void            autoDrawEnable(AutoDraw);
        void            autoDrawDisable(AutoDraw);
        
        Flags<Feature>  features() const;
        bool            feature(Feature) const;
        void            featureEnable(Feature);
        void            featureDisable(Feature);
        
        QPen            sceneRectPen() const;
        QBrush          sceneRectBrush() const;

        void            setMouseWheelZoomModifiers(Qt::KeyboardModifiers);
        void            setSceneRectPen(QPen);
        void            setSceneRectBrush(QBrush);
        
        void            setTool(GraphicsTool*);
        
        QSize           sizeHint() const override;

        //! Zoom factor
        double          zoomFactor() const;
        
        GraphicsTool*   tool() const;

    public slots:
        //! Adjusts the zoom to fit the scene
        void            fitToScene();
        
        //! Zooms in one step
        void            zoomIn();

        //! Zooms out one step
        void            zoomOut();
        
        //! Sets the zoom factor
        void            setZoomFactor(double);
        
    signals:
        //! Advertises the current mouse position in the view
        void            mouseAt(double, double);
        
        void            zoomChanged(double);
        
        void            viewportResized();
        void            resized();
    
    protected:
    
        //! Scroll wheel event handler (override)
        void            wheelEvent(QWheelEvent *event) override;
        
        //! Mouse move event handler (override)
        void            mouseMoveEvent(QMouseEvent*) override;
        
        void            resizeEvent(QResizeEvent*) override;

        void            drawBackground(QPainter *painter, const QRectF &rect) override;
        
        void            drawSceneRect(QPainter *painter, const QRectF &rect={});
        
        bool            viewportEvent(QEvent*) override;
        
    private:

        GraphicsScene* const    m_scene;
    
        Flags<AutoDraw>         m_autoDraw;
        Flags<Feature>          m_features;
        QBrush                  m_sceneRectBrush;
        QPen                    m_sceneRectPen;
        Qt::KeyboardModifiers   m_mouseWheelZoomModifiers = {};
        GraphicsTool*           m_tool          = nullptr;
    };
}
