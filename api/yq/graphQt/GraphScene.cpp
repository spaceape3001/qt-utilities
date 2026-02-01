////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/gluon/logging.hpp>

#include "GraphScene.hpp"
#include "GraphScene.hxx"

#include <yq/gluon/core/upoint.hpp>
#include <yq/gluon/core/uvector.hpp>
#include <yq/graph/GDocument.hpp>
#include <yq/symbol/Symbol.hpp>

namespace yq::gluon {

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

    void    GraphScene::_update_connected(GNode)
    {
    }

    GraphScene::Item*   GraphScene::add(GBase gb)
    {
        if(!gb)
            return nullptr;
        if(gb.document() != m_graph.document())
            return nullptr;
            
        if(m_items.contains(gb.id()))
            return nullptr;
            
        Item*   ret = nullptr;
            
        if(GEdge ge = (GEdge) gb)
            ret = add_edge(ge);
        if(GLine gl = (GLine) gb)
            ret = add_line(gl);
        if(GNode gn = (GNode) gb)
            ret = add_node(gn);
        if(GPort gp = (GPort) gb)
            ret = add_port(gp);
        if(GShape gs = (GShape) gs)
            ret = add_shape(gs);
        if(GText gt = (GText) gb)
            ret = add_text(gt);

        if(ret){
            if(QGraphicsItem* it = ret->qItem()){ [[likely]]
                addItem(it);
            } else {
                m_notQt.push_back(ret);
            }
            m_items[gb.id()]    = ret;
        }
        return ret;
    }


    GraphScene::Node*       GraphScene::add_node(GNode n)
    {
        return new Node(*this, n);
    }
    
    GraphScene::Edge*       GraphScene::add_edge(GEdge ge)
    {
        return new Edge(*this, ge);
    }
    
    GraphScene::Port*       GraphScene::add_port(GPort)
    {
        // might not be a qgraphicsitem....
        return nullptr;
    }
    
    GraphScene::Line*       GraphScene::add_line(GLine gl)
    {
        return new Line(*this, gl);
    }
    
    GraphScene::Shape*      GraphScene::add_shape(GShape)
    {
        return nullptr;
    }
    
    GraphScene::Text*       GraphScene::add_text(GText)
    {
        return nullptr;
    }
    

    GraphScene::Node*    GraphScene::add(const GNodeTemplateCPtr& gnt, const QPointF& pt)
    {
        if(!gnt)    
            return nullptr;
            
        GNode   node    = m_graph.node(CREATE, *gnt);
        node.position(SET, yVector(pt));
        return static_cast<Node*>(add(node));
    }
    
    void    GraphScene::clear()
    {
        m_items.clear();
        GraphicsScene::clear();
        for(Item* it : m_notQt)
            delete it;
        m_notQt.clear();
    }

    GGraph      GraphScene::get() const
    {
        return m_graph;
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

    //////////////////////////////////////////////////////////////////////////////
    GraphScene::Edge::Edge(GraphScene&gs, GEdge e) : Item(gs), m_data(e)
    {
        _init();
    }
    
    GraphScene::Edge::~Edge()
    {
    }
    
    void GraphScene::Edge::_init()
    {
    }

    //////////////////////////////////////////////////////////////////////////////

    GraphScene::Item::Item(GraphScene& gs) : m_scene(gs)
    {
    }
    GraphScene::Item::~Item() = default;

    //////////////////////////////////////////////////////////////////////////////

    GraphScene::Line::Line(GraphScene& gs, GLine gl) : Item(gs), m_data(gl)
    {
    }
    
    GraphScene::Line::~Line()
    {
    }
    
    void GraphScene::Line::_init()
    {
    }

    //////////////////////////////////////////////////////////////////////////////


    ////  Node(const Node&);  // pending/TODO
    //GraphScene::Node::Node(const GNodeTemplateCPtr& gnt, const QPointF& pt)
    //{
        //m_template  = gnt;
        ////m_data      = // TODO
        ////m_data.position     = { (float) pt.x(), (float) pt.y() };
        ////m_data.size         = { 100.f, 50.f };  // hack
        //_init();
        //setPos(pt);
    //}
    
    GraphScene::Node::Node(GraphScene& gs, GNode gn) : Item(gs), m_data(gn)
    {
        m_template  = GNodeTemplate::IO::load(gn.type());
        _init();
        setPos(qPoint(m_data.position()));
    }
    
    GraphScene::Node::~Node()
    {
    }
    
    void    GraphScene::Node::_init()
    {
        SymbolCPtr  sym = _symbol();
        if(!sym)
            return ;
            
        //clear();
        build(*sym, m_scene.m_symSize);
    }

    SymbolCPtr  GraphScene::Node::_symbol() const
    {
        if(m_template && !m_template->symbol.empty()){
            return Symbol::IO::load(m_template->symbol);
        }
        return Symbol::IO::load("pp:yq/symbol/basic.sym#circle");
    }

    void    GraphScene::Node::position(set_k, const Vector2D& pt)
    {
        m_data.position(SET, pt);
        setPos(qPoint(pt));
        
        if(GraphScene* sc = dynamic_cast<GraphScene*>(scene()))
            sc -> _update_connected(m_data);
    }
    
    void    GraphScene::Node::position(set_k, const QPointF& pt)
    {
        position(SET, yVector(pt));
    }

    QPointF  GraphScene::Node::position() const 
    {
        return qPoint(m_data.position());
    }
    
}

#include "moc_GraphScene.cpp"
