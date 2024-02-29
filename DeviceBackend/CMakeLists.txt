qt_add_library(devicebackend STATIC)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    SerialBus
    Network
)

set_target_properties(devicebackend PROPERTIES AUTOMOC ON)
target_link_libraries(devicebackend
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus
    PRIVATE Qt${QT_VERSION_MAJOR}::Network
)

qt_add_qml_module(devicebackend
    URI DeviceBackend
    VERSION 1.0
    SOURCES
        devicelineno.h
        devicecenter.h
        devicecenter.cpp
        devicescanner.h
        devicescanner.cpp
        deviceplc.h
        deviceplc.cpp
        devicerobot.h
        devicerobot.cpp
        struct/logstruct.h
        struct/logstruct.cpp
        struct/hdatetime.h
        struct/hdatetime.cpp
        worker/tcpworker.h
        worker/tcpworker.cpp
        worker/tcpworkersender.h
        worker/tcpworkersender.cpp
        worker/modbustcpworker.h
        worker/modbustcpworker.cpp
        worker/modbustcpworkersender.h
        worker/modbustcpworkersender.cpp
        worker/httpaddlogworker.h
        worker/httpaddlogworker.cpp
        worker/hdatetimeworker.h
        worker/hdatetimeworker.cpp
        centworker/scannerworker.h
        centworker/scannerworker.cpp
        centworker/plcworker.h
        centworker/plcworker.cpp
        centworker/robotworker.h
        centworker/robotworker.cpp
        centworker/schedulingworker.h
        centworker/schedulingworker.cpp
)
