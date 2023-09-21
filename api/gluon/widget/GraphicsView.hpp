////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsView>

namespace yq::gluon {
    /*! \brief Enhanced GraphicsView
    */
    class GraphicsView : public QGraphicsView {
        Q_OBJECT
    public:
    
        //! Steps to double zoom
        static constexpr const unsigned kDOUBLE = 8;    // eight steps to double
    
        //! Constructor
        GraphicsView(QGraphicsScene*, QWidget*parent=nullptr);
        
        //! Destructor
        ~GraphicsView();
        
        //! Zoom factor
        double      zoomFactor() const;
        
    public slots:
        //! Adjusts the zoom to fit the scene
        void        fitToScene();
        
        //! Zooms in one step
        void        zoomIn();

        //! Zooms out one step
        void        zoomOut();
        
        //! Sets the zoom factor
        void        setZoomFactor(double);
        
    signals:
        //! Advertises the current mouse position in the view
        void    mouseAt(double, double);
    
    protected:
    
        //! Scroll wheel event handler (override)
        void    wheelEvent(QWheelEvent *event) override;
        
        //! Mouse move event handler (override)
        void    mouseMoveEvent(QMouseEvent*) override;
    };
}
