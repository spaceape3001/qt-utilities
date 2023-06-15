################################################################################
##
##  YOUR QUILL
##
################################################################################

project(gluon)

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED 

    gluon/app/Application.hpp
    gluon/app/Application.ipp
    gluon/app/MainWindow.hpp
    gluon/app/MainWindow.ipp
    gluon/app/SimpleEditor.hpp
    gluon/app/SimpleEditor.ipp
    gluon/app/SubWindow.hpp
    gluon/app/SubWindow.ipp
    gluon/app/UndoSubWindow.hpp
    gluon/app/UndoSubWindow.ipp
    gluon/app/app.cpp

    gluon/core/IgCaseQ.hpp
    gluon/core/IgCaseQ.ipp
    gluon/core/RefQ.hpp
    gluon/core/RefQ.ipp
    gluon/core/Utilities.hpp
    gluon/core/Utilities.ipp
    gluon/core/core.cpp

    gluon/delegate/ColorComboBoxDelegate.hpp
    gluon/delegate/ColorComboBoxDelegate.ipp
    gluon/delegate/ColorDelegate.hpp
    gluon/delegate/ColorDelegate.ipp
    gluon/delegate/Delegate.hpp
    gluon/delegate/Delegate.ipp
    gluon/delegate/DirBoxDelegate.hpp
    gluon/delegate/DirBoxDelegate.ipp
    gluon/delegate/FileBoxDelegate.hpp
    gluon/delegate/FileBoxDelegate.ipp
    gluon/delegate/IconBarDelegate.hpp
    gluon/delegate/IconBarDelegate.ipp
    gluon/delegate/ImageDelegate.hpp
    gluon/delegate/ImageDelegate.ipp
    gluon/delegate/IntegerDelegate.hpp
    gluon/delegate/IntegerDelegate.ipp
    gluon/delegate/NullableDateDelegate.hpp
    gluon/delegate/NullableDateDelegate.ipp
    gluon/delegate/NullableDateTimeDelegate.hpp
    gluon/delegate/NullableDateTimeDelegate.ipp
    gluon/delegate/delegate.cpp

    gluon/edit/CheckBox.hpp
    gluon/edit/CheckBox.ipp
    gluon/edit/ColorChip.hpp
    gluon/edit/ColorChip.ipp
    gluon/edit/ColorComboBox.hpp
    gluon/edit/ColorComboBox.ipp
    gluon/edit/ComboBox.hpp
    gluon/edit/ComboBox.ipp
    gluon/edit/DateEdit.hpp
    gluon/edit/DateEdit.ipp
    gluon/edit/DateTimeEdit.hpp
    gluon/edit/DateTimeEdit.ipp
    gluon/edit/DirBox.hpp
    gluon/edit/DirBox.ipp
    gluon/edit/DoubleSpinBox.hpp
    gluon/edit/DoubleSpinBox.ipp
    gluon/edit/DropListComboBox.hpp
    gluon/edit/DropListComboBox.ipp
    gluon/edit/EnumComboBox.hpp
    gluon/edit/EnumComboBox.ipp
    gluon/edit/FileBox.hpp
    gluon/edit/FileBox.ipp
    gluon/edit/NullableDateEdit.hpp
    gluon/edit/NullableDateEdit.ipp
    gluon/edit/NullableDateTimeEdit.hpp
    gluon/edit/NullableDateTimeEdit.ipp
    gluon/edit/LineEdit.hpp
    gluon/edit/LineEdit.ipp
    gluon/edit/SpinBox.hpp
    gluon/edit/SpinBox.ipp
    gluon/edit/StringMapEdit.hpp
    gluon/edit/StringMapEdit.ipp
    gluon/edit/StringMapEditModel.hpp
    gluon/edit/StringMapEditView.hpp
    gluon/edit/StringSetCheck.hpp
    gluon/edit/StringSetCheck.ipp
    gluon/edit/TextEdit.hpp
    gluon/edit/TextEdit.ipp
    gluon/edit/TimeEdit.hpp
    gluon/edit/TimeEdit.ipp
    gluon/edit/edit.cpp

    gluon/io/ZipFile.cpp
    gluon/io/ZipReader.hpp
    gluon/io/ZipWriter.hpp

    gluon/layout/BorderLayout.cpp
    gluon/layout/BorderLayout.hpp
    gluon/layout/FlowLayout.cpp
    gluon/layout/FlowLayout.hpp

    gluon/model/GridTickModel.hpp
    gluon/model/GridTickModel.ipp
    gluon/model/StandardGridTickModel.hpp
    gluon/model/StandardGridTickModel.ipp
    gluon/model/model.cpp
    
    gluon/undo/UndoBase.cpp
    gluon/undo/UndoBase.hpp

    gluon/widget/Button.cpp
    gluon/widget/Button.hpp
    gluon/widget/DrawRuler.hpp
    gluon/widget/DrawRuler.ipp
    gluon/widget/FormWidget.hpp
    gluon/widget/FormWidget.ipp
    gluon/widget/WidgetTabBar.hpp
    gluon/widget/WidgetTabBar.ipp
    gluon/widget/WidgetTabWidget.hpp
    gluon/widget/WidgetTabWidget.ipp
    gluon/widget/widget.cpp
)    

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        YQ_USE_QT6=1
    PRIVATE
        YQ_QMAKE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yqtoolbox
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

LinkTest(${PROJECT_NAME})


