################################################################################
##
##  YOUR QUILL
##
################################################################################

project(qutil)

find_package(Qt5 REQUIRED Core Gui Widgets)

add_library(${PROJECT_NAME} SHARED 
    qu/core/IgCase.hpp
    qu/core/IgCase.ipp
    qu/core/core.cpp

    qu/edit/CheckBox.ipp
    qu/edit/CheckBox.hpp
    qu/edit/ColorChip.ipp
    qu/edit/ColorChip.hpp
    qu/edit/ColorCombo.ipp
    qu/edit/ColorCombo.hpp
    qu/edit/ComboBox.ipp
    qu/edit/ComboBox.hpp
    qu/edit/DateEdit.ipp
    qu/edit/DateEdit.hpp
    qu/edit/DateTimeEdit.hpp
    qu/edit/DateTimeEdit.ipp
    qu/edit/DirBox.ipp
    qu/edit/DirBox.hpp
    qu/edit/DoubleSpinBox.ipp
    qu/edit/DoubleSpinBox.hpp
    qu/edit/DropListComboBox.ipp
    qu/edit/DropListComboBox.hpp
    qu/edit/FileBox.ipp
    qu/edit/FileBox.hpp
    qu/edit/NullableDateEdit.ipp
    qu/edit/NullableDateEdit.hpp
    qu/edit/NullableDateTimeEdit.ipp
    qu/edit/NullableDateTimeEdit.hpp
    qu/edit/LineEdit.ipp
    qu/edit/LineEdit.hpp
    qu/edit/SpinBox.ipp
    qu/edit/SpinBox.hpp
    qu/edit/StringMapEdit.ipp
    qu/edit/StringMapEdit.hpp
    qu/edit/StringMapEditModel.hpp
    qu/edit/StringMapEditView.hpp
    qu/edit/StringSetCheck.ipp
    qu/edit/StringSetCheck.hpp
    qu/edit/TextEdit.ipp
    qu/edit/TextEdit.hpp
    qu/edit/TimeEdit.ipp
    qu/edit/TimeEdit.hpp
    qu/edit/edit.cpp

    qu/io/ZipFile.cpp
    
    qu/layout/BorderLayout.cpp
    qu/layout/BorderLayout.hpp
    qu/layout/FlowLayout.cpp
    qu/layout/FlowLayout.hpp
    
    qu/undo/UndoBase.cpp
    qu/undo/UndoBase.hpp
    
    qu/widget/Button.cpp
    qu/widget/Button.hpp
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
        yqtoolbox
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

LinkTest(${PROJECT_NAME})


