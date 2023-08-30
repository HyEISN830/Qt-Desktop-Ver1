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

    property string device1Port: "?"
    property string device2Port: "?"
    property string device3Port: "?"
    property string device4Port: "?"
    property string device5Port: "?"
    property string device6Port: "?"
    property string device7Port: "?"
    property string device8Port: "?"
    property string device9Port: "?"

    property bool device1Connected: false
    property bool device2Connected: false
    property bool device3Connected: false
    property bool device4Connected: false
    property bool device5Connected: false
    property bool device6Connected: false
    property bool device7Connected: false
    property bool device8Connected: false
    property bool device9Connected: false

    property int maxDeviceCtn: 0
    property list<var> deviceList: []
    property var deviceListChangedCb: null
}
