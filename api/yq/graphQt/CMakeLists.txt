################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_graphQt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED 
    GNodeNewMimeData.hpp
    GNodeNewMimeData.cpp
    GNodePalette.hpp
    GNodePalette.cpp
    GraphCanvas.hpp
    GraphCanvas.cpp
    GraphScene.hpp
    GraphScene.hxx
    GraphScene.cpp
    GraphTextItem.hpp
    GraphView.hpp
    GraphView.cpp
)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_gluon
        yq_graph
        yq_graphicsQt
        yq_symbol
        yq_symbolQt
)

yq_qtlib(${PROJECT_NAME})
LinkTest(${PROJECT_NAME})

