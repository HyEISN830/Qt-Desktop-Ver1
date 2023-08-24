qt_add_library(qmlfontloader STATIC)

set_target_properties(qmlfontloader PROPERTIES AUTOMOC ON)
target_link_libraries(qmlfontloader
    PRIVATE Qt${QT_VERSION_MAJOR}::Quick
)

list(APPEND MODULE_FONTLOADER_QML_FILES
    DirectoryFontLoader.qml
)

qt_add_qml_module(qmlfontloader
    URI QmlFontLoader
    VERSION 1.0
    QML_FILES
        ${MODULE_FONTLOADER_QML_FILES}
    RESOURCES
        fonts/JetBrainsMono-Regular.ttf
        fonts/MiSans-Regular.ttf
        fonts/MiSans-Normal.ttf
)
