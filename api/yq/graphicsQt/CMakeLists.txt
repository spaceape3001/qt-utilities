################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_graphicsQt)

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED 
    GraphicsCanvas.hpp
    GraphicsCanvas.cpp
    GraphicsLayer.hpp
    GraphicsLayer.cpp
    GraphicsScene.hpp
    GraphicsScene.cpp
    GraphicsTool.hpp
    GraphicsTool.cpp
    GraphicsView.hpp
    GraphicsView.cpp
    GraphicsVisibility.cpp
)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_gluon
        yq_resource
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

LinkTest(${PROJECT_NAME})


