################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.23.0)
project(QtUtilities VERSION 0.0.0.3)

if(NOT YOUR_QUILL_TOOLBOX)
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/yq-toolbox)
        include(yq-toolbox/configure.cmake)
        add_subdirectory(yq-toolbox)
    else()
        message(FATAL_ERROR "Currently this must be a submodule to the project, and the toolbox already added!")
    endif()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

include(configure.cmake)

add_subdirectory(api)

