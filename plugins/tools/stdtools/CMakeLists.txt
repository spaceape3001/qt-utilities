################################################################################
##
##  YOUR QUILL
##
################################################################################

project(stdtools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED
    #GeneralTool.hpp
    #GeneralTool.cpp
    MoveTool.hpp
    MoveTool.cpp
    PanTool.hpp
    PanTool.cpp
    SelectTool.hpp
    SelectTool.cpp
)

target_link_libraries(${PROJECT_NAME}
    yq_graphicsQt
)
LinkTest(${PROJECT_NAME})
