////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq/graphicsQt/GraphicsCanvas.hpp>
#include <yq/graphicsQt/GraphicsTool.hpp>
#include <yq/graphicsQt/GraphicsScene.hpp>
#include <yq/graphicsQt/GraphicsView.hpp>

namespace yq::gluon {
    template <typename S, typename V> 
    std::pair<S*,V*>        GraphicsTool::sceneViewAs() const
    {
        auto [sc,vi] = sceneView();
        return { dynamic_cast<S*>(sc), dynamic_cast<V*>(vi) };
    }
    
    template <typename S, typename V, typename C>
    std::tuple<S*,V*,C*>    GraphicsTool::contextAs() const
    {
        auto [sc,vi,cv] = context();
        return { dynamic_cast<S*>(sc), dynamic_cast<V*>(vi), dynamic_cast<C*>(cv) };
    }
}
