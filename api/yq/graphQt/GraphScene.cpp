////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>

#include "GraphNodeItem.hpp"
#include "GraphEdgeItem.hpp"
#include "GraphLineItem.hpp"
#include "GraphPortItem.hpp"
#include "GraphScene.hpp"
#include "GraphShapeItem.hpp"
#include "GraphTextItem.hpp"

#include <yq/errors.hpp>
#include <yq/gluon/core/ugraphics.hpp>
#include <yq/gluon/core/upoint.hpp>
#include <yq/gluon/core/uvector.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/symbol/Symbol.hpp>
#include <yq/symbolQt/SymbolGraphicsItem.hxx>

namespace yq::gluon {
    struct GraphScene::PathBuilder {
        const GraphScene&   scene;
        QPainterPath        path;
        bool                moveNext    = true;
        
        PathBuilder(const GraphScene& sc) : scene(sc){}
        ~PathBuilder(){};
        
        std::error_code _point(const QPointF& pt)
        {
            if(moveNext){
                path.moveTo(pt);
                moveNext    = false;
            } else {
                path.lineTo(pt);
            }
            return {};
        }
        
        std::error_code _gid(gid_t id)
        {
            const GraphItem* it     = scene.item(id);
            if(!it)
                return create_error<"Bad/Invalid Graph ID">();
            const QGraphicsItem* qi = it->qItem();
            if(!qi)
                return create_error<"ID to non-item">();
            return _point(qCenterPoint(*qi));
        }

        std::error_code _waypoint(const GWaypoint& way)
        {
            // right now...ignore direction
            if(std::get_if<std::monostate>(&way.position)){
                return {};
            } else if(auto p = std::get_if<Vector2D>(&way.position)){
                _point(qPoint(*p));
                return {};
            } else if(auto p = std::get_if<gid_t>(&way.position)){
                return _gid(*p);
            } else {
                return errors::todo();
            }
        }
        
        std::error_code    add(const path_spec_t& ps)
        {
            if(auto p = std::get_if<QPointF>(&ps)){
                return _point(*p);
            } else if(auto p = std::get_if<gid_t>(&ps)){
                return _gid(*p);
            } else if(auto p = std::get_if<GWaypoint>(&ps)){
                return _waypoint(*p);
            } else if(auto p = std::get_if<wayspan_t>(&ps)){
                for(auto& w : *p){
                    if(auto ec = _waypoint(w); ec != std::error_code()) 
                        return ec;
                }
                return {};
            }

            return create_error<"Unspecified path spec">();
        }
        
        PathBuilder& operator<<(const path_spec_t& ps)
        {
            if(auto ec = add(ps); ec != std::error_code()){
                gluonInfo  << "Unable to route ... " << ec.message();
            }
            return *this;
        }
    };

    GraphScene::GraphScene(GGraph gph, QObject*parent) : GraphicsScene(parent), m_graph(gph)
    {
        if(!gph)
            gph = GGraph(CREATE);
        set(gph);
        //makeCheckerboardBackgroundBrush();    // not working well
    }
    
    GraphScene::GraphScene(QObject*parent) : GraphScene(GGraph(), parent)
    {
    }
    
    GraphScene::~GraphScene()
    {
        clear();
    }

    GraphItem*   GraphScene::add(GBase gb)
    {
        if(!gb)
            return nullptr;
        if(gb.document() != m_graph.document())
            return nullptr;
            
        if(m_items.contains(gb.id()))
            return m_items[gb.id()];
            
        GraphItem*   ret = nullptr;
            
        if(GEdge ge = (GEdge) gb)
            ret = new GraphEdgeItem(*this, ge);
        if(GLine gl = (GLine) gb)
            ret = new GraphLineItem(*this, gl);
        if(GNode gn = (GNode) gb)
            ret = add_node(gn);
        //if(GPort gp = (GPort) gb)
            //ret = new GraphPortItem(*this, gp); 
        if(GShape gs = (GShape) gs)
            ret = new GraphShapeItem(*this, gs);
        if(GText gt = (GText) gb)
            ret = new GraphTextItem(*this, gt);

        if(ret){
            if(QGraphicsItem* it = dynamic_cast<QGraphicsItem*>(ret)){ 
                addItem(it);
            } else {
                m_notQt.push_back(ret);
            }
            m_items[gb.id()]    = ret;
        }
        return ret;
    }

    GraphNodeItem*    GraphScene::add(const GNodeTemplateCPtr& gnt, const QPointF& pt)
    {
        if(!gnt)    
            return nullptr;
            
        GNode   node    = m_graph.node(CREATE, *gnt);
        node.position(SET, yVector(pt));
        return static_cast<GraphNodeItem*>(add(node));
    }

    GraphNodeItem*      GraphScene::add_node(GNode node)
    {
        GraphNodeItem* gni  = new GraphNodeItem(*this, node);
        std::vector<GPort>  ports   = node.ports();
        auto&               pins    = gni -> pins();
        
        // Create ports (if necessary)
        for(size_t n = ports.size(); n<pins.size(); ++n)
            ports.push_back(node.port(CREATE, pins[n].pin));
        for(size_t n = 0; n<pins.size(); ++n){
            GraphPortItem*  gpi = new GraphPortItem(*this, ports[n], pins[n].item);
            gni -> m_ports.push_back(gpi);
            m_items[ports[n].id()]  = gpi;
        }
        return gni;
    }
    
    void    GraphScene::clear()
    {
        m_items.clear();
        GraphicsScene::clear();
        for(GraphItem* it : m_notQt)
            delete it;
        m_notQt.clear();
    }

    void        GraphScene::dirty(gid_t gid)
    {
        m_dirty << gid;
    }

    GGraph      GraphScene::get() const
    {
        return m_graph;
    }

    GraphItem*          GraphScene::item(gid_t g)
    {
        return m_items.get(g, nullptr);
    }
    
    const GraphItem*    GraphScene::item(gid_t g) const
    {
        return m_items.get(g, nullptr);
    }

    QPainterPath    GraphScene::path_for(std::initializer_list<path_spec_t> ps) const
    {
        PathBuilder     pb(*this);
        for(const auto& p : ps)
            pb << p;
        return pb.path;
    }

    void        GraphScene::set(GGraph g)
    {
        if(!g)
            return ;
        m_graph = g;
        clear();
        for(GBase b : g.children())
            add(b);
    }

    void    GraphScene::update()
    {
        for(gid_t g : m_dirty){
            if(GraphItem*it  = m_items.get(g, nullptr))
                it -> update();
        }
        m_dirty.clear();
        invalidate();
    }
    
    void    GraphScene::updateAll()
    {
        for(auto & itr : m_items)
            if(itr.second)
                itr.second -> update();
        invalidate();
    }
}

#include "GraphEdgeItem.ipp"
#include "GraphItem.ipp"
#include "GraphLineItem.ipp"
#include "GraphNodeItem.ipp"
#include "GraphPortItem.ipp"
#include "GraphShapeItem.ipp"
#include "GraphTextItem.ipp"
#include "moc_GraphScene.cpp"
#include "moc_GraphTextItem.cpp"

