################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_gluon)

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_library(${PROJECT_NAME} SHARED 

    app/Application.hpp
    app/Application.cpp
    app/Dock.hpp
    app/Dock.cpp
    app/MainWindow.hpp
    app/MainWindow.cpp
    app/SimpleEditor.hpp
    app/SimpleEditor.cpp
    app/SubWindow.hpp
    app/SubWindow.cpp
    app/UndoMainWindow.hpp
    app/UndoMainWindow.cpp
    app/UndoSubWindow.hpp
    app/UndoSubWindow.cpp

    core/Action.hpp
    core/Action.cpp
    core/FileName.hpp
    core/FileName.cpp
    core/IgCaseQ.hpp
    #core/IgCaseQ.cpp
    core/Logging.hpp
    core/Logging.cpp
    core/ObjectQ.cpp
    core/QtTypes.hpp
    core/QtTypes.cpp
    core/RefQ.hpp
    core/RefQ.cpp
    core/Utilities.hpp
    core/WidgetQ.cpp
    core/utility.cpp

    delegate/ColorComboBoxDelegate.hpp
    delegate/ColorComboBoxDelegate.cpp
    delegate/ColorDelegate.hpp
    delegate/ColorDelegate.cpp
    delegate/Delegate.hpp
    delegate/Delegate.cpp
    delegate/DirBoxDelegate.hpp
    delegate/DirBoxDelegate.cpp
    delegate/FileBoxDelegate.hpp
    delegate/FileBoxDelegate.cpp
    delegate/IconBarDelegate.hpp
    delegate/IconBarDelegate.cpp
    delegate/ImageDelegate.hpp
    delegate/ImageDelegate.cpp
    delegate/IntegerDelegate.hpp
    delegate/IntegerDelegate.cpp
    delegate/NullableDateDelegate.hpp
    delegate/NullableDateDelegate.cpp
    delegate/NullableDateTimeDelegate.hpp
    delegate/NullableDateTimeDelegate.cpp
    delegate/StringComboDelegate.hpp
    delegate/StringComboDelegate.cpp
    delegate/StringDelegate.hpp
    delegate/StringDelegate.cpp
    delegate/UIntegerDelegate.hpp
    delegate/UIntegerDelegate.cpp

    edit/CheckBox.hpp
    edit/CheckBox.cpp
    edit/ColorChip.hpp
    edit/ColorChip.cpp
    edit/ColorComboBox.hpp
    edit/ColorComboBox.cpp
    edit/ComboBox.hpp
    edit/ComboBox.cpp
    edit/DateEdit.hpp
    edit/DateEdit.cpp
    edit/DateTimeEdit.hpp
    edit/DateTimeEdit.cpp
    edit/DirBox.hpp
    edit/DirBox.cpp
    edit/DoubleSpinBox.hpp
    edit/DoubleSpinBox.cpp
    edit/DropListComboBox.hpp
    edit/DropListComboBox.cpp
    edit/EnumComboBox.hpp
    edit/EnumComboBox.cpp
    edit/FileBox.hpp
    edit/FileBox.cpp
    edit/NullableDateEdit.hpp
    edit/NullableDateEdit.cpp
    edit/NullableDateTimeEdit.hpp
    edit/NullableDateTimeEdit.cpp
    edit/LineEdit.hpp
    edit/LineEdit.cpp
    edit/SpinBox.hpp
    edit/SpinBox.cpp
    edit/StringMapEdit.hpp
    edit/StringMapEdit.cpp
    edit/StringMapEditModel.hpp
    edit/StringMapEditView.hpp
    edit/StringSetCheck.hpp
    edit/StringSetCheck.cpp
    edit/TextEdit.hpp
    edit/TextEdit.cpp
    edit/TimeEdit.hpp
    edit/TimeEdit.cpp

    filter/filter.cpp

    io/ZipFile.cpp
    io/ZipReader.hpp
    io/ZipWriter.hpp
    
    interface/PositionInterface.cpp

    layout/FlowLayout.cpp
    layout/FlowLayout.hpp

    model/GridTickModel.hpp
    model/GridTickModel.cpp
    model/StandardGridTickModel.hpp
    model/StandardGridTickModel.cpp
    
    undo/UndoBase.cpp
    undo/UndoBase.hpp
    
    util/Int64SignalMapper.hpp
    util/Int64SignalMapper.cpp
    util/UInt64SignalMapper.hpp
    util/UInt64SignalMapper.cpp
    
    validator/IdentifierValidator.hpp
    validator/IdentifierValidator.cpp
    validator/NoSpacesValidator.hpp
    validator/NoSpacesValidator.cpp
    validator/XmlIdentifierValidator.hpp
    validator/XmlIdentifierValidator.cpp

    widget/Button.cpp
    widget/Button.hpp
    widget/DrawRuler.hpp
    widget/DrawRuler.cpp
    widget/FormWidget.hpp
    widget/FormWidget.cpp
    widget/PaletteWidget.hpp
    widget/PaletteWidget.cpp
    widget/ScrollBar.hpp
    widget/ScrollBar.cpp
    widget/WidgetTabBar.hpp
    widget/WidgetTabBar.cpp
    widget/WidgetTabWidget.hpp
    widget/WidgetTabWidget.cpp
    
    ${QT_DIR}/res/yqStdResources.qrc
)    

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${GLUON_API_DIR}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        YQ_USE_QT6=1
    PRIVATE
        YQ_QMAKE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        yq_core
        yq_resource
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

LinkTest(${PROJECT_NAME})


