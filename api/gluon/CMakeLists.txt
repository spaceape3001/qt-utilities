################################################################################
##
##  YOUR QUILL
##
################################################################################

project(yq_gluon)

find_package(Qt6 REQUIRED Core Gui Widgets )
set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED 
    app/Application.hpp
    app/Application.ipp
    app/MainWindow.hpp
    app/MainWindow.ipp
    app/SimpleEditor.hpp
    app/SimpleEditor.ipp
    app/SubWindow.hpp
    app/SubWindow.ipp
    app/UndoSubWindow.hpp
    app/UndoSubWindow.ipp
    app/app.cpp

    core/IgCaseQ.hpp
    core/IgCaseQ.ipp
    core/QtTypes.hpp
    core/QtTypes.ipp
    core/RefQ.hpp
    core/RefQ.ipp
    core/Utilities.hpp
    core/Utilities.ipp
    core/core.cpp

    delegate/ColorComboBoxDelegate.hpp
    delegate/ColorComboBoxDelegate.ipp
    delegate/ColorDelegate.hpp
    delegate/ColorDelegate.ipp
    delegate/Delegate.hpp
    delegate/Delegate.ipp
    delegate/DirBoxDelegate.hpp
    delegate/DirBoxDelegate.ipp
    delegate/FileBoxDelegate.hpp
    delegate/FileBoxDelegate.ipp
    delegate/IconBarDelegate.hpp
    delegate/IconBarDelegate.ipp
    delegate/ImageDelegate.hpp
    delegate/ImageDelegate.ipp
    delegate/IntegerDelegate.hpp
    delegate/IntegerDelegate.ipp
    delegate/NullableDateDelegate.hpp
    delegate/NullableDateDelegate.ipp
    delegate/NullableDateTimeDelegate.hpp
    delegate/NullableDateTimeDelegate.ipp
    delegate/StringComboDelegate.hpp
    delegate/StringComboDelegate.ipp
    delegate/StringDelegate.hpp
    delegate/StringDelegate.ipp
    delegate/UIntegerDelegate.hpp
    delegate/UIntegerDelegate.ipp
    delegate/delegate.cpp

    edit/CheckBox.hpp
    edit/CheckBox.ipp
    edit/ColorChip.hpp
    edit/ColorChip.ipp
    edit/ColorComboBox.hpp
    edit/ColorComboBox.ipp
    edit/ComboBox.hpp
    edit/ComboBox.ipp
    edit/DateEdit.hpp
    edit/DateEdit.ipp
    edit/DateTimeEdit.hpp
    edit/DateTimeEdit.ipp
    edit/DirBox.hpp
    edit/DirBox.ipp
    edit/DoubleSpinBox.hpp
    edit/DoubleSpinBox.ipp
    edit/DropListComboBox.hpp
    edit/DropListComboBox.ipp
    edit/EnumComboBox.hpp
    edit/EnumComboBox.ipp
    edit/FileBox.hpp
    edit/FileBox.ipp
    edit/NullableDateEdit.hpp
    edit/NullableDateEdit.ipp
    edit/NullableDateTimeEdit.hpp
    edit/NullableDateTimeEdit.ipp
    edit/LineEdit.hpp
    edit/LineEdit.ipp
    edit/SpinBox.hpp
    edit/SpinBox.ipp
    edit/StringMapEdit.hpp
    edit/StringMapEdit.ipp
    edit/StringMapEditModel.hpp
    edit/StringMapEditView.hpp
    edit/StringSetCheck.hpp
    edit/StringSetCheck.ipp
    edit/TextEdit.hpp
    edit/TextEdit.ipp
    edit/TimeEdit.hpp
    edit/TimeEdit.ipp
    edit/edit.cpp

    filter/filter.cpp

    graph/GraphModel.hpp
    graph/GraphModel.ipp
    graph/graph.cpp

    graph/data/GraphBase.hpp
    graph/data/GraphBase.ipp
    graph/data/GraphDocument.hpp
    graph/data/GraphDocument.ipp
    graph/data/GraphEdge.hpp
    graph/data/GraphEdge.ipp
    graph/data/GraphGraph.hpp
    graph/data/GraphGraph.ipp
    graph/data/GraphName.hpp
    graph/data/GraphName.ipp
    graph/data/GraphNode.hpp
    graph/data/GraphNode.ipp
    graph/data/GraphPin.hpp
    graph/data/GraphPin.ipp
    graph/data/GraphPinned.hpp
    graph/data/GraphPinned.ipp
    graph/data/GraphProperty.hpp
    graph/data/GraphProperty.ipp
    graph/data/GraphSocket.hpp
    graph/data/GraphSocket.ipp

    io/ZipFile.cpp
    io/ZipReader.hpp
    io/ZipWriter.hpp

    layout/BorderLayout.cpp
    layout/BorderLayout.hpp
    layout/FlowLayout.cpp
    layout/FlowLayout.hpp

    model/GridTickModel.hpp
    model/GridTickModel.ipp
    model/StandardGridTickModel.hpp
    model/StandardGridTickModel.ipp
    model/model.cpp
    
    undo/UndoBase.cpp
    undo/UndoBase.hpp
    
    util/Int64SignalMapper.hpp
    util/Int64SignalMapper.cpp
    util/UInt64SignalMapper.hpp
    util/UInt64SignalMapper.cpp
    
    validator/IdentifierValidator.hpp
    validator/IdentifierValidator.ipp
    validator/NoSpacesValidator.hpp
    validator/NoSpacesValidator.ipp
    validator/XmlIdentifierValidator.hpp
    validator/XmlIdentifierValidator.ipp
    validator/validator.cpp

    widget/Button.cpp
    widget/Button.hpp
    widget/DrawRuler.hpp
    widget/DrawRuler.ipp
    widget/FormWidget.hpp
    widget/FormWidget.ipp
    widget/GraphicsView.hpp
    widget/GraphicsView.ipp
    widget/WidgetTabBar.hpp
    widget/WidgetTabBar.ipp
    widget/WidgetTabWidget.hpp
    widget/WidgetTabWidget.ipp
    widget/widget.cpp
)    

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/..
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
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

LinkTest(${PROJECT_NAME})


