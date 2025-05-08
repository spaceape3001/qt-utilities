////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QFrame>
#include <yq/core/Ref.hpp>
#include <gluon/model/GridTickModel.hpp>

namespace yq::gluon {
    class DrawRuler;
    class GridTickModel;
    class GraphicsScene;
    class GraphicsView;
    class ScrollBar;
    
    class GraphicsWidget : public QFrame {
        Q_OBJECT
    public:
        
        struct Config {
            ScrollBar*              horzScroll  = nullptr;
            Ref<GridTickModel>      horzTicks;
            QWidget*                neCorner    = nullptr;
            QWidget*                nwCorner    = nullptr;
            GraphicsScene*          scene       = nullptr;
            QRectF                  sceneRect   = {};
            QWidget*                seCorner    = nullptr;
            QWidget*                swCorner    = nullptr;
            ScrollBar*              vertScroll  = nullptr;
            Ref<GridTickModel>      vertTicks;
            GraphicsView*           view        = nullptr;  //! View... if it & scene are specified, assume to be bound
            
            Config(){}
        };
    
        GraphicsWidget(const Config& cfg=Config(), QWidget* parent=nullptr);
        ~GraphicsWidget();
        
        GraphicsScene*          scene() { return m_scene; }
        const GraphicsScene*    scene() const { return m_scene; }
        GraphicsView*           view() { return m_view; }
        const GraphicsView*     view() const { return m_view; }
        
        GridTickModel*          horz_ticks() { return m_horz.ticks.ptr(); };
        GridTickModel*          vert_ticks() { return m_vert.ticks.ptr(); }
    
    signals:
        //! Advertises the current mouse position in the view
        void    mouseAt(double, double);

    private:
        struct {
            DrawRuler*          ruler   = nullptr;
            ScrollBar*          scroll  = nullptr;
            Ref<GridTickModel>  ticks;
        }                       m_horz, m_vert;

        GraphicsScene*          m_scene = nullptr;
        GraphicsView*           m_view  = nullptr;
    };
}
