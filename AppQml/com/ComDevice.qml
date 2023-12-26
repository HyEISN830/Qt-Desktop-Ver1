import QtQuick
import Qt5Compat.GraphicalEffects

Item {
    property string iconPath: ""    // = "../" + iconPath
    property string iconColor: "#7e6aa9ff"
    property int dId: -1
    property string title: "Title"
    property string content: "Content"
    property bool connected: false

    id: comDevice
    width: 300
    height: 80

    Rectangle {
        id: plcItem
        width: parent.width
        height: parent.height
        color: "#dcdde1"
        radius: height / 15

        Column {
            id: status
            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            spacing: 3

            Row {
                spacing: 3

                Rectangle {
                    id: rxLed
                    y: 1.5
                    width: height
                    height: txtRx.height - 3
                    color: "#ff4757"
                    radius: height

                    ColorAnimation {
                        id: rxLedHAni
                        target: rxLed
                        property: "color"
                        from: "#ff4757"
                        to: "#2ecc71"
                        duration: 35
                        easing.type: Easing.InOutQuad
                        onFinished: rxLedLAni.start()
                    }

                    ColorAnimation {
                        id: rxLedLAni
                        target: rxLed
                        property: "color"
                        from: "#2ecc71"
                        to: "#ff4757"
                        duration: 50
                        easing.type: Easing.InOutQuad
                    }
                }

                ComTextEdit {
                    id: txtRx
                    text: "接收"
                }
            }

            Row {
                spacing: 3

                Rectangle {
                    id: txLed
                    y: 1.5
                    width: height
                    height: txtTx.height - 3
                    color: "#ff4757"
                    radius: height

                    ColorAnimation {
                        id: txLedHAni
                        target: txLed
                        property: "color"
                        from: "#ff4757"
                        to: "#2ecc71"
                        duration: 5
                        easing.type: Easing.InOutQuad
                        onFinished: txLedLAni.start()
                    }

                    ColorAnimation {
                        id: txLedLAni
                        target: txLed
                        property: "color"
                        from: "#2ecc71"
                        to: "#ff4757"
                        duration: 50
                        easing.type: Easing.InOutQuad
                    }
                }

                ComTextEdit {
                    id: txtTx
                    text: "发送"
                }
            }

            Row {
                spacing: 3

                Rectangle {
                    id: connLed
                    y: 1.5
                    width: height
                    height: txtConn.height - 3
                    color: connected ? "#2ecc71" : "#ff4757"
                    radius: height
                }

                ComTextEdit {
                    id: txtConn
                    text: connected ? "已连接" : "未连接"
                }
            }
        }

        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: -3
            anchors.right: icon.left
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.left: status.right
            anchors.leftMargin: 5
            color: "transparent"

            Column {
                anchors.centerIn: parent
                spacing: 2

                ComTextEditBold {
                    font.pixelSize: 18
                    text: title
                }

                ComTextEdit {
                    font.pixelSize: 14
                    text: content
                }

                ComTextEdit {
                    font.pixelSize: 12
                    text: "设备Id: " + dId
                }
            }
        }

        Rectangle {
            id: icon
            anchors.top: parent.top
            anchors.topMargin: 3
            anchors.rightMargin: 3
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 3
            width: parent.height - (anchors.topMargin + anchors.bottomMargin)
            radius: height
            color: iconColor

            Image {
                source: iconPath.length ? ("../" + iconPath) : "../resources/device.png"
                anchors.centerIn: parent
                width: 45
                height: 45
            }
        }

        NumberAnimation {
            id: plcItemLargeAni
            target: plcItem
            property: "scale"
            to: 1.14
            duration: 200
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            id: plcItemNormalAni
            target: plcItem
            property: "scale"
            to: 1.0
            duration: 200
            easing.type: Easing.InOutQuad
        }

        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onEntered: plcItemLargeAni.start()
            onExited: plcItemNormalAni.start()
        }
    }

    function rx() {
        rxLedHAni.start()
    }

    function tx() {
        txLedHAni.start()
    }

    function conn(c) {
        connLed.color = c ? "#2ecc71" : "#ff4757"
        txtConn.text = c ? "已连接" : "未连接"
    }
}
