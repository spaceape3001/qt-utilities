cmake_minimum_required(VERSION 3.23.0)

if("${PROJECT_NAME}" STREQUAL "")
    project(YourQuill VERSION 0.0.0.3)
    
    #   TODO.... add in verbage
    if(NOT YQ_TOOLBOX_DIR)
        message(FATAL_ERROR "Need to know where Your Quill's toolbox is.")
    endif()
    
    include(${YQ_TOOLBOX_DIR}/YourQuill.cmake)
endif()



