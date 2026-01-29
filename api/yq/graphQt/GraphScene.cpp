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


    GraphScene::Node*       GraphScene::add_node(GNode)
    {
        return nullptr;
    }
    
    GraphScene::Edge*       GraphScene::add_edge(GEdge)
    {
        return nullptr;
    }
    
    GraphScene::Port*       GraphScene::add_port(GPort)
    {
        return nullptr;
    }
    
    GraphScene::Line*       GraphScene::add_line(GLine)
    {
        return nullptr;
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
        Node*   n   = new Node(node);
        addItem(n);
        return n;
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

    GraphScene::Item::Item() = default;
    GraphScene::Item::~Item() = default;

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
    
    GraphScene::Node::Node(GNode gn) : m_data(gn)
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
        build(*sym, m_size);
    }

    SymbolCPtr  GraphScene::Node::_symbol() const
    {
        if(m_template && !m_template->symbol.empty()){
            return Symbol::IO::load(m_template->symbol);
        }
        return Symbol::IO::load("pp:yq/symbol/basic.sym#circle");
    }

    void    GraphScene::Node::setPosition(const Vector2D& pt)
    {
        m_data.position(SET, pt);
        setPos(qPoint(pt));
    }
    
    void    GraphScene::Node::setPosition(const QPointF& pt)
    {
        m_data.position(SET, yVector(pt));
        setPos(pt);
    }

    QPointF  GraphScene::Node::getPosition() const 
    {
        return qPoint(m_data.position());
    }
    
}

#include "moc_GraphScene.cpp"
