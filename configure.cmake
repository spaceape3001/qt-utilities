################################################################################
##
##  YOUR QUILL
##
################################################################################

if(NOT YOUR_QUILL_QTUTIL)
    #set(CMAKE_AUTOMOC ON)
    #set(CMAKE_AUTORCC ON)
    set(YOUR_QUILL_QTUTIL ${CMAKE_CURRENT_LIST_DIR})
endif()

if(NOT COMMAND qt_library)
    #   Append for all qt based libraries
    set(GLOBAL PROPERTY YQ_QT_LIBRARIES)  
    set(GLOBAL PROPERTY YQ_QT_DATA)  
    
    #   Use this macro for non-tachyon libraries
    macro(qt_library target)
        message("Qt library ${target}")
        get_property(tmp GLOBAL PROPERTY YQ_QT_LIBRARIES)
        #get_target_property(tgt ${target} LIBRARY_OUTPUT_NAME)
        list(APPEND tmp ${target})
        set_property(GLOBAL PROPERTY YQ_QT_LIBRARIES ${tmp})
    endmacro()
    macro(qt_data dir)
        set(full "${CMAKE_CURRENT_LIST_DIR}/${dir}")
        message("Qt data ${full}")
        get_property(tmp GLOBAL PROPERTY YQ_QT_DATA)
        #get_target_property(tgt ${target} LIBRARY_OUTPUT_NAME)
        list(APPEND tmp ${full})
        set_property(GLOBAL PROPERTY YQ_QT_DATA ${tmp})
    endmacro()

    macro(qt_config)
        if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_LIST_DIR})
            get_property(QT_LIBARIES GLOBAL PROPERTY YQ_QT_LIBRARIES)
            get_property(QT_DATA GLOBAL PROPERTY YQ_QT_DATA)
            configure_file(${QT_DIR}/qt.cfg.in ${CMAKE_BINARY_DIR}/bin/qt.cfg)
        endif()
    endmacro()
endif()
