////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphView.hpp"
#include "GraphScene.hpp"
#include "GNodeNewMimeData.hpp"

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

namespace yq::gluon {
    GraphView::GraphView(QWidget* parent) : GraphicsView(new GraphScene, parent), 
        m_scene(static_cast<GraphScene*>(GraphicsView::scene()))
    {
        assert(m_scene);
    }
    
    GraphView::GraphView(GraphScene*sc, QWidget* parent) : GraphicsView(sc ? sc : new GraphScene, parent),
        m_scene(static_cast<GraphScene*>(GraphicsView::scene()))
    {
        assert(m_scene);
        if(!sc)
            m_scene -> setParent(this);
    }
    
    GraphView::~GraphView()
    {
    }


    void    GraphView::dragEnterEvent(QDragEnterEvent*evt)
    {
        if(dynamic_cast<const GNodeNewMimeData*>(evt->mimeData())){
            evt -> accept();
        } else {
            evt -> ignore();
        }
    }

    void    GraphView::dragLeaveEvent(QDragLeaveEvent*evt) 
    {
    }
    
    void    GraphView::dragMoveEvent(QDragMoveEvent*evt) 
    {
    
    }
    
    void    GraphView::dropEvent(QDropEvent* evt) 
    {
        if(const GNodeNewMimeData* nm = dynamic_cast<const GNodeNewMimeData*>(evt->mimeData())){
            m_scene -> add(nm->node(), mapToScene(evt->position().toPoint()));
        }
    }
}

#include "moc_GraphView.cpp"
