################################################################################
##
##  YOUR QUILL
##
################################################################################

project(qutil)

find_package(Qt5 REQUIRED Core Gui Widgets)

add_library(${PROJECT_NAME} SHARED 
    qu/io/ZipFile.cpp
    qu/undo/CheckBox.cpp
    qu/undo/CheckBox.hpp
    qu/undo/ColorChip.cpp
    qu/undo/ColorChip.hpp
    qu/undo/ColorCombo.cpp
    qu/undo/ColorCombo.hpp
    qu/undo/ComboBox.cpp
    qu/undo/ComboBox.hpp
    qu/undo/UndoBase.cpp
    qu/undo/UndoBase.hpp
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        YQ_USE_QT5=1
    PRIVATE
        YQ_QMAKE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

LinkTest(${PROJECT_NAME})


