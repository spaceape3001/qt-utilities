////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QGraphicsScene>

namespace yq::gluon {

    //! More of a stub for now so common functionality can be added
    class GraphicsScene : public QGraphicsScene {
        Q_OBJECT
    public:
        GraphicsScene(QObject *parent = nullptr);
        GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);
        GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
        ~GraphicsScene();
    };
}
