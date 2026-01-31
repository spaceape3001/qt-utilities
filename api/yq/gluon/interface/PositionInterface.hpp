////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

// Not bothering with forward declarations for the handlers 
// (Figure if the handler's needed, the Qt class's already 
// being included.)

#include <QPointF>  

namespace yq::gluon {
    struct PositionInterface {
        virtual ~PositionInterface(){}
        virtual QPointF  position() const = 0;
        virtual void	 position(set_k, const QPointF&) {}
    };
}
