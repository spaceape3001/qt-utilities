////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>

namespace yq::gluon {
    /*! \brief Collection of graphics items
    */
    class GraphicsLayer : public QObject {
        Q_OBJECT
    public:
        GraphicsLayer(QObject*parent=nullptr);
        ~GraphicsLayer();
    private:
    
    };
}
