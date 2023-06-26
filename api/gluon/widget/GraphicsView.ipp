////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "GraphicsView.hpp"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QWheelEvent>

namespace yq::gluon {
    GraphicsView::GraphicsView(QGraphicsScene*scene, QWidget*parent) : QGraphicsView(scene, parent)
    {
        assert(scene);
        setMouseTracking(true);
    }
    
    GraphicsView::~GraphicsView()
    {
    }
        
    
    void    GraphicsView::fitToScene()
    {
        QGraphicsScene* sc  = scene();
        if(sc){
            fitInView(sc->sceneRect(), Qt::KeepAspectRatio);
        }
    }

    void    GraphicsView::mouseMoveEvent(QMouseEvent*evt)
    {
        QPointF     pt  = mapToScene(evt->pos());
        emit mouseAt(pt.x(), pt.y());
        QGraphicsView::mouseMoveEvent(evt);
    }

    void    GraphicsView::setZoomFactor(double z)
    {
        z           = fabs(z);
        double  old = zoomFactor();
        scale(z/old, z/old);
    }

    
    void    GraphicsView::wheelEvent(QWheelEvent *evt)
    {
        Qt::KeyboardModifiers   mods = evt->modifiers();
        if(mods & Qt::ControlModifier){
            double  factor  = pow(2.0, evt->angleDelta().y() / (120.0 * kDOUBLE));
            scale(factor, factor);
            evt->accept();
        } else 
            QGraphicsView::wheelEvent(evt);
    }

    double  GraphicsView::zoomFactor() const
    {
        QTransform  t   = transform();
        return sqrt(fabs(t.m11()*t.m22()-t.m12()*t.m21()));
    }
    
    
    void    GraphicsView::zoomIn()
    {
        static double   kFactorIn    = pow(2.0, 1.0/kDOUBLE);
        scale(kFactorIn, kFactorIn);
    }
    
    void    GraphicsView::zoomOut()
    {
        static double   kFactorOut    = pow(2.0, 1.0/kDOUBLE);
        scale(kFactorOut, kFactorOut);
    }
    
    
}

