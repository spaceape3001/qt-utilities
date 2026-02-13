////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graph/GGraph.hpp>
#include <yq/graph/GWaypoint.hpp>
#include <yq/graphicsQt/GraphicsScene.hpp>
#include <yq/typedef/g_node_template.hpp>
#include <yq/typedef/symbol.hpp>

class QPainterPath;

namespace yq::gluon {
    class GraphItem;
    class GraphNodeItem;
    
    class GraphScene : public GraphicsScene {
        Q_OBJECT
    public:
        GraphScene(GGraph, QObject*parent=nullptr);
        GraphScene(QObject*parent=nullptr);
        ~GraphScene();

        GraphNodeItem*   add(const GNodeTemplateCPtr&, const QPointF&);
        GraphItem*   add(GBase);
        //one for the document too
        
        void        set(GGraph);
        GGraph      get() const;

        // TODO
        //bool            set(const XGDocument&);
        //XGDocumentPtr   get() const;

        /*
            I *was* assuming retaining the document... better to 
            push it into items and pull it back.  Load/Export sort 
            of thing.
        */
        
        //struct Edge;
        //struct Line;
        //struct Text;
        
        float           symSize() const { return m_symSize; }
        void            updateConnected(GNode);
        
        using path_spec_t   = std::variant<std::monostate, gid_t, QPointF>; // and more to come....
        
        QPainterPath    path_for(std::initializer_list<path_spec_t>) const;
        
        
    public slots:
        void    clear();    // name shadow is deliberate
        
    private:
    
        GraphNodeItem*      add_node(GNode);
    
        GGraph                      m_graph;
        std::map<gid_t, GraphItem*> m_items;
        std::vector<GraphItem*>     m_notQt;
        float                       m_symSize   = 32.;
        
    };
}
