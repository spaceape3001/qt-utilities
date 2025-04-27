################################################################################
##
##  YOUR QUILL
##
################################################################################

cmake_minimum_required(VERSION 3.23.0)
project(QtUtilities VERSION 0.0.0.3 LANGUAGES CXX)

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/yq-toolbox)
    message(FATAL_ERROR "YQ toolbox must be present! (use a symbolic link or junction)")
endif()

include(local.cmake OPTIONAL)
include(configure.cmake)
include(yq-toolbox/standard.cmake)
YQRepo()

