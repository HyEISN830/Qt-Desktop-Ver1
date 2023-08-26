cmake_minimum_required(VERSION 3.16)

project(Qt-Desktop-Ver1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    SerialBus
    Sql
)

qt_standard_project_setup(REQUIRES 6.5)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/windows.rc")

list(APPEND RESOURCE_FILES
    resources/icon-help-globle.svg
)

list(APPEND MODULE_MAIN_QML_COMPONENT_FILES
    maincom/ComHelpDialog.qml
)

qt_add_executable(appQt-Desktop-Ver1
    main.cpp
    ${app_icon_resource_windows}
)

qt_add_qml_module(appQt-Desktop-Ver1
    URI AC_OU_CMS
    VERSION 1.0
    QML_FILES
        Main.qml
        ${MODULE_MAIN_QML_COMPONENT_FILES}
    RESOURCES
        ${RESOURCE_FILES}
)

qt_add_resources(appQt-Desktop-Ver1 "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

set_target_properties(appQt-Desktop-Ver1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER hyeisn.cn
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

list(APPEND PROJECT_MODULES
    PRIVATE appqml
    PRIVATE appqmlplugin
    PRIVATE appqmlbackend
    PRIVATE appqmlbackendplugin
    PRIVATE qmlfontloader
    PRIVATE qmlfontloaderplugin
    PRIVATE dbentity
    PRIVATE dbentityplugin
)

add_subdirectory(AppQml)
add_subdirectory(AppQmlBackend)
add_subdirectory(QmlFontLoader)
add_subdirectory(DbEntity)

target_link_libraries(appQt-Desktop-Ver1
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    PRIVATE Qt${QT_VERSION_MAJOR}::Gui
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::Qml
    PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
    ${PROJECT_MODULES}
)

install(TARGETS appQt-Desktop-Ver1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
