pragma Singleton
import QtQuick

QtObject {
    property string device1Ip: "?"
    property string device2Ip: "?"
    property string device3Ip: "?"
    property string device4Ip: "?"
    property string device5Ip: "?"
    property string device6Ip: "?"
    property string device7Ip: "?"
    property string device8Ip: "?"
    property string device9Ip: "?"
    property string device10Ip: "?"
    property string device11Ip: "?"
    property string device12Ip: "?"
    property string device13Ip: "?"
    property string device14Ip: "?"
    property string device15Ip: "?"

    property string device1Port: "?"
    property string device2Port: "?"
    property string device3Port: "?"
    property string device4Port: "?"
    property string device5Port: "?"
    property string device6Port: "?"
    property string device7Port: "?"
    property string device8Port: "?"
    property string device9Port: "?"
    property string device10Port: "?"
    property string device11Port: "?"
    property string device12Port: "?"
    property string device13Port: "?"
    property string device14Port: "?"
    property string device15Port: "?"

    property bool device1Connected: false
    property bool device2Connected: false
    property bool device3Connected: false
    property bool device4Connected: false
    property bool device5Connected: false
    property bool device6Connected: false
    property bool device7Connected: false
    property bool device8Connected: false
    property bool device9Connected: false
    property bool device10Connected: false
    property bool device11Connected: false
    property bool device12Connected: false
    property bool device13Connected: false
    property bool device14Connected: false
    property bool device15Connected: false

    property int maxDeviceCtn: 0
    property list<var> deviceList: []
    property var deviceMap: ({})
    property var deviceListChangedCb: null
    property TextEdit txtLog: null
}
