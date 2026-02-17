////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "GraphNodeItem.hpp"

#include <yq/gluon/core/upoint.hpp>
#include <yq/gluon/core/uvector.hpp>
#include <yq/graph/GNodeTemplate.hpp>
#include <yq/graphQt/GraphScene.hpp>
#include <yq/symbol/Symbol.hpp>

namespace yq::gluon {
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
    
    GraphNodeItem::GraphNodeItem(GraphScene& gs, GNode gn) : GraphItem(gs), m_data(gn)
    {
        m_template  = GNodeTemplate::IO::load(gn.type());
        _init();
        setPos(qPoint(m_data.position()));
    }
    
    GraphNodeItem::~GraphNodeItem()
    {
    }
    
    void    GraphNodeItem::_init()
    {
        SymbolCPtr  sym = _symbol();
        if(!sym)
            return ;
            
        //clear();
        build(*sym, m_scene.symSize());
    }

    SymbolCPtr  GraphNodeItem::_symbol() const
    {
        if(m_template && !m_template->symbol.empty()){
            return Symbol::IO::load(m_template->symbol);
        }
        return Symbol::IO::load("pp:yq/symbol/basic.sym#circle");
    }

    void    GraphNodeItem::position(set_k, const Vector2D& pt)
    {
        m_data.position(SET, pt);
        setPos(qPoint(pt));
        m_scene.updateConnected(m_data);
    }
    
    void    GraphNodeItem::position(set_k, const QPointF& pt)
    {
        position(SET, yVector(pt));
    }

    void     GraphNodeItem::position(move_k, const QPointF&del) 
    {
        position(SET, position() + del);
    }

    QPointF  GraphNodeItem::position() const 
    {
        return qPoint(m_data.position());
    }

    void GraphNodeItem::update() 
    {
        setPos(qPoint(m_data.position()));
        setVisible(!m_data.deleted());
    }
}
