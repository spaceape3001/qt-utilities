////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphScene.hpp"
#include "GraphScene.hxx"
#include <yq/symbol/Symbol.hpp>

namespace yq::gluon {

    GraphScene::GraphScene(QObject*parent) : GraphicsScene(parent)
    {
    }
    
    GraphScene::~GraphScene()
    {
    }

    GraphScene::Node*    GraphScene::add(const GNodeTemplateCPtr& gnt, const QPointF& pt)
    {
        if(!gnt)    
            return nullptr;
        Node*   n   = new Node(gnt, pt);
        addItem(n);
        return n;
    }
    
    #if 0

    bool            XGSceneQt::set(const XGDocument&doc)
    {
        return true;
    }
    
    XGDocumentPtr   XGSceneQt::get() const
    {
        return new XGDocument;
    }
    
    #endif

    //////////////////////////////////////////////////////////////////////////////

    GraphScene::Item::Item() = default;
    GraphScene::Item::~Item() = default;

    //////////////////////////////////////////////////////////////////////////////


    //  Node(const Node&);  // pending/TODO
    GraphScene::Node::Node(const GNodeTemplateCPtr& gnt, const QPointF& pt)
    {
        m_template  = gnt;
        //m_data      = // TODO
        //m_data.position     = { (float) pt.x(), (float) pt.y() };
        //m_data.size         = { 100.f, 50.f };  // hack
        _init();
        setPos(pt);
    }
    
    //Node(const GNodeTemplateCPtr&, const GNodeData&);   // TODO
    //Node(const GNodeData&);   // TODO
    
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
}

#include "moc_GraphScene.cpp"
