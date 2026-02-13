////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>

#include "GraphView.hpp"

#include <yq/graphQt/GNodeNewMimeData.hpp>
#include <yq/graphQt/GraphEdgeItem.hpp>
#include <yq/graphQt/GraphLineItem.hpp>
#include <yq/graphQt/GraphNodeItem.hpp>
#include <yq/graphQt/GraphPointCapture.hpp>
#include <yq/graphQt/GraphPortItem.hpp>
#include <yq/graphQt/GraphScene.hpp>
#include <yq/graphQt/GraphShapeItem.hpp>
#include <yq/graphQt/GraphTextItem.hpp>
#include <yq/text/format.hpp>
#include <yq/text/join.hpp>

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

    GraphPointCapture   GraphView::capture(QSinglePointEvent*evt) const
    {
        if(!evt)
            return {};
        return capture(WIDGET, evt->position(), CaptureOptions());
    }
    
    GraphPointCapture   GraphView::capture(QSinglePointEvent*evt, const CaptureOptions& options) const
    {
        if(!evt)
            return {};
        return capture(WIDGET, evt->position(), options);
    }
    

    GraphPointCapture   GraphView::capture(widget_k, const QPointF& pt) const
    {
        return capture(WIDGET, pt, CaptureOptions());
    }
    
    std::string         captureStringFormat(const GraphView::CaptureOptions& opts)
    {
        Vector<std::string_view> bits;
        if(opts.edges)
            bits << "EDGES";
        if(opts.items)
            bits << "ITEMS";
        if(opts.lines)
            bits << "LINES";
        if(opts.nodes)
            bits << "NODES";
        if(opts.ports)
            bits << "PORTS";
        if(opts.shapes)
            bits << "SHAPES";
        if(opts.texts)
            bits << "TEXTS";
        return join(bits, " ");
    }
    
    GraphPointCapture   GraphView::capture(widget_k, const QPointF& pt, const CaptureOptions& opts) const
    {
        //gluonInfo  << "GraphView::capture(WIDGET, " << pt << ", {" << captureStringFormat(opts) << "}";
    
        GraphPointCapture   ret;
        QTransform  t   = viewportTransform();
        QTransform  ti  = t.inverted();
        ret.position    = pt;
        ret.point       = ti.map(pt);

        if(!m_scene)
            return {};
            
        QRectF      rect(pt-QPointF(0.5,0.5), pt+QPointF(0.5,0.5));
        
        for(QGraphicsItem* it : m_scene -> items(ti.map(rect), Qt::IntersectsItemShape, Qt::DescendingOrder, t)){
            if(!it)
                continue;
                
            if(!ret.qItem)
                ret.qItem   = it;
            
            if(opts.nodes && !ret.node){
                ret.node    = dynamic_cast<GraphNodeItem*>(it);
                if(ret.node)
                    ret.qItem   = ret.node;

                if(opts.ports && ret.node && !ret.port){
                    QPointF p2  = it -> mapFromScene(ret.point);
                    for(GraphPortItem* gpn : ret.node->ports()){
                        QGraphicsItem*  pItem   = gpn->qItem();
                        if(!pItem)
                            continue;
                        if(pItem->contains(p2)){
                            ret.port    = gpn;
                            ret.qItem   = pItem;
                            break;
                        }
                    }
                }
            }

            if(opts.ports && !ret.port){
                ret.port    = dynamic_cast<GraphPortItem*>(it);
                if(ret.port)
                    ret.qItem   = it;
            }
            
            
            if(opts.edges && !ret.edge){ 
                // TODO
            }
            
            if(opts.shapes && !ret.shape){
                // TODO
            }
            
            if(opts.lines && !ret.line){
                // TODO
            }
            
            if(opts.texts && !ret.text){
                // TODO
            }
        }
        
        return ret;
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
