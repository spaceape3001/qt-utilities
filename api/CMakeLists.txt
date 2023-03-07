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
    
    qu/delegate/ColorComboBoxDelegate.hpp
    qu/delegate/ColorComboBoxDelegate.ipp
    qu/delegate/ColorDelegate.hpp
    qu/delegate/ColorDelegate.ipp
    qu/delegate/Delegate.hpp
    qu/delegate/Delegate.ipp
    qu/delegate/DirBoxDelegate.hpp
    qu/delegate/DirBoxDelegate.ipp
    qu/delegate/FileBoxDelegate.hpp
    qu/delegate/FileBoxDelegate.ipp
    qu/delegate/IconBarDelegate.hpp
    qu/delegate/IconBarDelegate.ipp
    qu/delegate/ImageDelegate.hpp
    qu/delegate/ImageDelegate.ipp
    qu/delegate/IntegerDelegate.hpp
    qu/delegate/IntegerDelegate.ipp
    qu/delegate/NullableDateDelegate.hpp
    qu/delegate/NullableDateDelegate.ipp
    qu/delegate/NullableDateTimeDelegate.hpp
    qu/delegate/NullableDateTimeDelegate.ipp
    qu/delegate/delegate.cpp

    qu/edit/CheckBox.hpp
    qu/edit/CheckBox.ipp
    qu/edit/ColorChip.hpp
    qu/edit/ColorChip.ipp
    qu/edit/ColorComboBox.hpp
    qu/edit/ColorComboBox.ipp
    qu/edit/ComboBox.hpp
    qu/edit/ComboBox.ipp
    qu/edit/DateEdit.hpp
    qu/edit/DateEdit.ipp
    qu/edit/DateTimeEdit.hpp
    qu/edit/DateTimeEdit.ipp
    qu/edit/DirBox.hpp
    qu/edit/DirBox.ipp
    qu/edit/DoubleSpinBox.hpp
    qu/edit/DoubleSpinBox.ipp
    qu/edit/DropListComboBox.hpp
    qu/edit/DropListComboBox.ipp
    qu/edit/EnumComboBox.hpp
    qu/edit/EnumComboBox.ipp
    qu/edit/FileBox.hpp
    qu/edit/FileBox.ipp
    qu/edit/NullableDateEdit.hpp
    qu/edit/NullableDateEdit.ipp
    qu/edit/NullableDateTimeEdit.hpp
    qu/edit/NullableDateTimeEdit.ipp
    qu/edit/LineEdit.hpp
    qu/edit/LineEdit.ipp
    qu/edit/SpinBox.hpp
    qu/edit/SpinBox.ipp
    qu/edit/StringMapEdit.hpp
    qu/edit/StringMapEdit.ipp
    qu/edit/StringMapEditModel.hpp
    qu/edit/StringMapEditView.hpp
    qu/edit/StringSetCheck.hpp
    qu/edit/StringSetCheck.ipp
    qu/edit/TextEdit.hpp
    qu/edit/TextEdit.ipp
    qu/edit/TimeEdit.hpp
    qu/edit/TimeEdit.ipp
    qu/edit/edit.cpp

    qu/io/ZipFile.cpp
    
    qu/layout/BorderLayout.cpp
    qu/layout/BorderLayout.hpp
    qu/layout/FlowLayout.cpp
    qu/layout/FlowLayout.hpp
    
    qu/model/GridTickModel.hpp
    qu/model/GridTickModel.ipp
    qu/model/StandardGridTickModel.hpp
    qu/model/StandardGridTickModel.ipp
    qu/model/model.cpp
    
    qu/undo/UndoBase.cpp
    qu/undo/UndoBase.hpp
    
    qu/widget/Button.cpp
    qu/widget/Button.hpp
    qu/widget/DrawRuler.hpp
    qu/widget/DrawRuler.ipp
    qu/widget/widget.cpp
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


