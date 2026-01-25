################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_symbolQt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED 
    SymbolGraphicsItem.hpp
    SymbolGraphicsItem.cpp
)


target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_gluon
        yq_symbol
)

LinkTest(${PROJECT_NAME})

