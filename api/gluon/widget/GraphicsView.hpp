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
    
        static constexpr const unsigned kDOUBLE = 8;    // eight steps to double
    
        GraphicsView(QGraphicsScene*, QWidget*parent=nullptr);
        ~GraphicsView();
        
        double      zoomFactor() const;
        
    public slots:
        void        fitToScene();
        void        zoomIn();
        void        zoomOut();
        void        setZoomFactor(double);
        
    signals:
        void    mouseAt(double, double);
    
    protected:
        void    wheelEvent(QWheelEvent *event) override;
        void    mouseMoveEvent(QMouseEvent*) override;
    };
}
