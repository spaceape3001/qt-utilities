////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsWidget.hpp"

#include <gluon/widget/GraphicsView.hpp>
#include <gluon/widget/DrawRuler.hpp>
#include <gluon/widget/ScrollBar.hpp>
#include <gluon/model/GraphicsScene.hpp>
#include <gluon/model/StandardGridTickModel.hpp>

#include <QGridLayout>

namespace yq::gluon {
    GraphicsWidget::GraphicsWidget(const Config&cfg, QWidget* parent) : QFrame(parent)
    {
        ///////////////////////
        //  SCENE/WIDGETS/ETC
        
        if(cfg.scene){
            m_scene = cfg.scene;
        } else if(cfg.view && cfg.view->scene()){
            m_scene = dynamic_cast<GraphicsScene*>(cfg.view->scene());
            assert(m_scene && "GRAPHICS SCENE IS INVALID!");
        } else {
            m_scene = new GraphicsScene(this);  // arbitrary numbers....
        }

        if(cfg.sceneRect != QRectF()){
            m_scene -> setSceneRect(cfg.sceneRect);
        }
        
        if(m_scene->sceneRect() == QRectF())
            m_scene -> setSceneRect(0, 0, 1000, 1000);  //arbitrary numbers to prevent divide-by-zero
        
        if(cfg.view){
            m_view  = cfg.view;
        } else {
            m_view  = new GraphicsView(m_scene);
            m_view -> setScene(m_scene);
        }
        
        assert(m_scene && m_view->scene() && "GRAPHICS SCENE IS INVALID!");
        
        m_view -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_view -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        
        if(cfg.horzTicks){
            m_horz.ticks    = cfg.horzTicks;
        } else {
            m_horz.ticks    = new StandardGridTickModel(this);
        }
        
        m_horz.ruler        = new DrawRuler(Qt::Horizontal);
        m_horz.ruler->setModel(m_horz.ticks);
        
        if(cfg.vertTicks){
            m_vert.ticks    = cfg.vertTicks;
        } else {
            m_vert.ticks    = new StandardGridTickModel(this);
        }
        
        m_vert.ruler        = new DrawRuler(Qt::Vertical);
        m_vert.ruler->setModel(m_vert.ticks);
        
        if(cfg.horzScroll){
            m_horz.scroll   = cfg.horzScroll;
        } else {
            m_horz.scroll   = new ScrollBar(Qt::Horizontal);
        }
        
        if(cfg.vertScroll){
            m_vert.scroll   = cfg.vertScroll;
        } else {
            m_vert.scroll   = new ScrollBar(Qt::Vertical);
        }
        
        ///////////////////////
        //  SIZING
        m_horz.ruler  -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_horz.scroll -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        m_vert.ruler  -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_vert.scroll -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        m_view -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        
        ///////////////////////
        //  LAYOUT
        
        
        QGridLayout*    layout  = new QGridLayout;
        setLayout(layout);

        if(cfg.nwCorner){
            layout -> addWidget(cfg.nwCorner, 0, 0, Qt::AlignLeft|Qt::AlignTop);
        }
        
        layout->addWidget(m_horz.ruler, 0, 1, Qt::AlignHCenter|Qt::AlignTop);
        if(cfg.neCorner){
            layout -> addWidget(cfg.neCorner, 0, 0, Qt::AlignRight|Qt::AlignTop);
        }
        
        layout->addWidget(m_vert.ruler, 1, 0, Qt::AlignLeft|Qt::AlignVCenter);
        layout->addWidget(m_view, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);
        layout->addWidget(m_vert.scroll, 1, 2, Qt::AlignRight|Qt::AlignVCenter);
        
        if(cfg.swCorner){
            layout -> addWidget(cfg.swCorner, 2, 0, Qt::AlignLeft|Qt::AlignBottom);
        }
        
        layout->addWidget(m_horz.scroll, 2, 1, Qt::AlignHCenter|Qt::AlignBottom);
        
        if(cfg.seCorner){
            layout -> addWidget(cfg.seCorner, 2, 2, Qt::AlignRight|Qt::AlignBottom);
        }
        
        layout -> setColumnStretch(1,1);
        layout -> setRowStretch(1,1);
        layout -> setHorizontalSpacing(0);
        layout -> setVerticalSpacing(0);
        layout -> setContentsMargins(0,0,0,0);
        layout -> setSizeConstraint(QLayout::SetMaximumSize);
        
        ///////////////////////
        //  SIGNALS/SLOTS
    }
    
    GraphicsWidget::~GraphicsWidget()
    {
    }
}

#include "moc_GraphicsWidget.cpp"
