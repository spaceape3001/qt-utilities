################################################################################
##
##  YOUR QUILL
##
################################################################################

project(QtUtilities)

find_package(Qt5 REQUIRED Core Gui Widgets)

add_library(${PROJECT_NAME} SHARED 
    qt/io/ZipFile.cpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
)

LinkTest(${PROJECT_NAME})


