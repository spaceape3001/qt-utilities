////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/gluon/graphics/GraphicsScene.hpp>
#include <yq/typedef/g_node_template.hpp>
#include <yq/typedef/symbol.hpp>

namespace yq::gluon {
    class GraphScene : public GraphicsScene {
        Q_OBJECT
    public:
        struct Item;
        struct Node;
    
        GraphScene(QObject*parent=nullptr);
        ~GraphScene();

        Node*    add(const GNodeTemplateCPtr&, const QPointF&);
        //one for the document too

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

    };
}
