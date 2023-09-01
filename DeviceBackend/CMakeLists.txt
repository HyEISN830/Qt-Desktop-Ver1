qt_add_library(devicebackend STATIC)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
)

target_link_libraries(devicebackend
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
)

set_target_properties(devicebackend PROPERTIES AUTOMOC ON)
target_link_libraries(devicebackend
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus
)

qt_add_qml_module(devicebackend
    URI DeviceBackend
    VERSION 1.0
    SOURCES
        devicecenter.h
        devicecenter.cpp
        devicebarcodescanner.h
        devicebarcodescanner.cpp
        deviceplc.h
        deviceplc.cpp
)
