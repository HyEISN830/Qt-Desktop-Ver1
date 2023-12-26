qt_add_library(appqmlbackend STATIC)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    SerialBus
)

set_target_properties(appqmlbackend PROPERTIES AUTOMOC ON)
target_link_libraries(appqmlbackend
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus
)

list(APPEND MODULE_APPQMLBACKEND_CPP_FILES
    progmservice.h
    progmservice.cpp
    qmlservice.h
    qmlservice.cpp
)

qt_add_qml_module(appqmlbackend
    URI AppQmlBackend
    VERSION 1.0
    SOURCES
        ${MODULE_APPQMLBACKEND_CPP_FILES}
)
