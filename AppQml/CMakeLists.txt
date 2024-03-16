qt_add_library(appqml STATIC)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    Sql
)

target_link_libraries(appqml
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
)

set_target_properties(appqml PROPERTIES AUTOMOC ON)
target_link_libraries(appqml
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus
)

list(APPEND MODULE_QML_FILES
    GlobalVariable.qml
    GlobalEnums.qml
    Consts.qml
    PageMain.qml
    PageHome.qml
    PageWatching.qml
    PageTLogs.qml
    PageSets.qml
    T_PageTests.qml
)

list(APPEND MODULE_QML_COMPONENT_FILES
    com/ComDialog.qml
    com/ComLoading.qml
    com/ComSplitView.qml
    com/ComTextEdit.qml
    com/ComTextEditBold.qml
    com/ComLabel.qml
    com/ComTextField.qml
    com/ComButton.qml
    com/ComPane.qml
    com/ComDelay.qml
    com/ComDialogProgress.qml
    com/ComTable.qml
    com/ComList.qml
    com/ComToolTip.qml
    com/ComDevice.qml
    com/ComExpand.qml
    com/ComSwitch.qml
)

list(APPEND MODULE_APPQML_JS_FILES
    js/Common.js
)

list(APPEND MODULE_APPQML_CPP_FILES
    qmlcppdemo.h
    qmlcppdemo.cpp
)

list(APPEND MODULE_RESOURCES_FILES
    resources/icon-info.svg
    resources/icon-qust.svg
    resources/icon-erro.svg
    resources/icon-warn.svg
    resources/icon-settings.svg
    resources/icon-stats.svg
    resources/icon-home.svg
    resources/icon-settings-sliders.svg
    resources/icon-flask.svg
    resources/icon-shield.svg
    resources/icon-snowflakes.svg
    resources/icon-flame.svg
    resources/icon-reload.svg
    resources/icon-clean.svg
    resources/icon-change.svg
    resources/icon-success-green.svg
    resources/icon-arrow-left.svg
    resources/icon-arrow-right.svg
    resources/icon-angle-left.svg
    resources/icon-angle-right.svg
    resources/icon-location.svg
    resources/icon-camera.svg
    resources/icon-arrow-right-fill.svg
    resources/icon-document.svg
    resources/icon-play.svg
    resources/icon-pause.svg
    resources/icon-boxes.svg
    resources/icon-close.svg

    resources/home.jpg
    resources/logo.png
    resources/plc.png
    resources/device.png
    resources/barcode-scan.png
    resources/agv-robot.png
    resources/robotic-arm.png
    resources/task.png
    resources/home.jpg
    resources/logo.png
    resources/device.png
    resources/coming-soon-banner.png
)

set_source_files_properties(
    Consts.qml
    GlobalVariable.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE true
)

qt_add_qml_module(appqml
    URI AppQml
    VERSION 1.0
    SOURCES
        ${MODULE_APPQML_CPP_FILES}
    QML_FILES
        ${MODULE_QML_FILES}
        ${MODULE_QML_COMPONENT_FILES}
        ${MODULE_APPQML_JS_FILES}
    RESOURCES
        ${MODULE_RESOURCES_FILES}
)
