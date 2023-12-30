pragma Singleton
import QtQuick

QtObject {
    property string fontNormal: "MiSans Normal"
    property string fontBold: "MiSans"
    property string paneBgColor: "White"
    property int globalresolution_h: 900
    property int globalresolution_w: 1600
    property int icon_w: 16
    property int icon_h: 16
    property int button_h: 38
    property string tipFontColor: "White"
    property string versionStr: "1.1.0"

    // debug =========================================
    property bool debug: false
    property bool debug_enable_paraspage: true
}
