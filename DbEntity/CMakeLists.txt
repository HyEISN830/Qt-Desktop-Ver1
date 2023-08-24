qt_add_library(dbentity STATIC)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    Sql
    SerialBus
)

set_target_properties(dbentity PROPERTIES AUTOMOC ON)
target_link_libraries(dbentity
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
    PRIVATE Qt${QT_VERSION_MAJOR}::SerialBus
)

list(APPEND MODULE_DBENTITY_CPP_FILES
    baseentity.h
    baseentity.cpp
    parasmachine.h
    parasmachine.cpp
    parasparas.h
    parasparas.cpp
    tlogs.h
    tlogs.cpp
)

qt_add_qml_module(dbentity
    URI DbEntity
    VERSION 1.0
    SOURCES
        ${MODULE_DBENTITY_CPP_FILES}
)
