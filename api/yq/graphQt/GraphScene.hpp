////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsScene.hpp>
#include <yq/typedef/g_node_template.hpp>
#include <yq/typedef/symbol.hpp>
#include <yq/graph/GGraph.hpp>

namespace yq::gluon {
    class GraphScene : public GraphicsScene {
        Q_OBJECT
    public:
        struct Item;
        struct Node;
        struct Shape;
        struct Text;
        struct Port;
        struct Line;
        struct Edge;
    
        GraphScene(GGraph, QObject*parent=nullptr);
        GraphScene(QObject*parent=nullptr);
        ~GraphScene();

        Node*   add(const GNodeTemplateCPtr&, const QPointF&);
        Item*   add(GBase);
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
        
    public slots:
        void    clear();    // name shadow is deliberate
        
    private:
        GGraph                  m_graph;
        std::map<gid_t, Item*>  m_items;
        std::vector<Item*>      m_notQt;
        
        Node*       add_node(GNode);
        Edge*       add_edge(GEdge);
        Port*       add_port(GPort);
        Line*       add_line(GLine);
        Shape*      add_shape(GShape);
        Text*       add_text(GText);
    };
}
