////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/graph/Graph.hpp>
#include <QGraphicsScene>

namespace yq::gluon {
    
    class GraphNodeItem;
    class GraphEdgeItem;

    class GraphScene : public QGraphicsScene {
        Q_OBJECT
    public:
    
        GraphScene(GraphModel*, QObject*parent=nullptr);
        ~GraphScene();

        GraphNodeItem*  createNode(const QString& type, const QPointF& centerPt);
        GraphEdgeItem*  createEdge(const QString& type, GraphNodeItem*, const QString&, GraphNodeItem*, const QString&);

    private:
        GraphModel*     m_model = nullptr;
    };
}
