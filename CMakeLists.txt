cmake_minimum_required(VERSION 3.23.0)

if("${PROJECT_NAME}" STREQUAL "")
    project(YourQuill VERSION 0.0.0.3)
endif()

if(NOT YOUR_QUILL_TOOLBOX)
    message(FATAL_ERROR "Currently this must be a submodule to the project, and the toolbox already added!")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

include(configure.cmake)

add_subdirectory(api)

