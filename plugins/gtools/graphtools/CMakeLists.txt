################################################################################
##
##  YOUR QUILL
##
################################################################################

project(graphtools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED
    EdgeConnectorTool.cpp
    EdgeConnectorTool.hpp
    GraphLineTool.cpp
    GraphLineTool.hpp
    GraphTextTool.cpp
    GraphTextTool.hpp
    SuperGraphTool.cpp
    SuperGraphTool.hpp
)

target_link_libraries(${PROJECT_NAME}
    yq_graphQt
)
LinkTest(${PROJECT_NAME})
