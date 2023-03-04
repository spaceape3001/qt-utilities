if(NOT YOUR_QUILL_QTUTIL)

    if( "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
            # Mixing source and binary output is asking for trouble, best to avoid it
        message(SEND_ERROR "Building into the source directory is NOT recommended, choose another destination.")
    endif()

    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS "12.0.0")
            message(FATAL_ERROR "GCC version is obsolete, upgrade.")
        endif()
        SET(GCC ON)
    else()
        SET(GCC OFF)
    endif()

    if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
        set(CMAKE_GENERATOR "Unix Makefiles")
        get_filename_component(CMAKE_BUILD_TYPE ${CMAKE_BINARY_DIR} NAME)
    endif()
    
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    set(CMAKE_CONFIGURATION_TYPES Debug;Release)
    set(CMAKE_CXX_STANDARD 23)                  # C++23 is the standard (may be bumped in the future)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_DEBUG_POSTFIX D)

    set(YOUR_QUILL_QTUTIL ${CMAKE_CURRENT_LIST_DIR})
endif()

