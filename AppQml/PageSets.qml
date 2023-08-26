import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend

import "./js/Common.js" as JSLib

Item {
    property StackView view
    property QmlService bgservice: null

    id: page
    opacity: 0

    Rectangle {
        id: operateArea
        anchors.left: parent.left
        anchors.right: parent.right
        height: 30

        Row {
            anchors.fill: parent
            spacing: 8
            layoutDirection: Qt.RightToLeft

            ComButton {
                text: "收起全部"
                onClicked: {
                    for (let i in sets.children) {
                        sets.children[i].unexpandF()
                    }
                }
            }

            ComButton {
                text: "展开全部"
                onClicked: {
                    for (let i in sets.children) {
                        sets.children[i].expandF()
                    }
                }
            }
        }
    }

    ScrollView {
        id: setsView
        anchors.top: operateArea.bottom
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        padding: 0
        onWidthChanged: sets.width = setsView.width

        Column {
            id: sets
            spacing: 1

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 1 设置项 - PLC1"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 2 设置项 - PLC2"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 3 设置项 - W1扫码枪"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 4 设置项 - W2扫码枪"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 5 设置项 - W3扫码枪"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 6 设置项 - N1扫码枪"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 7 设置项 - N2扫码枪"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 8 设置项 - N3扫码枪"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: "设备Id: 9 设置项 - SJ AGV"
                body: Component {
                    Rectangle {
                        height: 100
                        color: "#f1f2f6"

                        Column {
                            anchors.fill: parent
                            anchors.topMargin: 6
                            anchors.leftMargin: 8
                            spacing: 8

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 10

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevideIp.width + txtDeviceIp.width
                                    height: txtDeviceIp.height

                                    ComLabel {
                                        id: lblDevideIp
                                        anchors.verticalCenter: txtDeviceIp.verticalCenter
                                        text: "IP: "
                                    }

                                    ComTextField {
                                        id: txtDeviceIp
                                        anchors.left: lblDevideIp.right
                                        placeholderText: "IP"
                                        width: 120
                                    }
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: lblDevicePort.width + txtDevicePort.width
                                    height: txtDevicePort.height

                                    ComLabel {
                                        id: lblDevicePort
                                        anchors.verticalCenter: txtDevicePort.verticalCenter
                                        text: "Port: "
                                    }

                                    ComTextField {
                                        id: txtDevicePort
                                        anchors.left: lblDevicePort.right
                                        placeholderText: "PORT"
                                        width: 120
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                }

                                ComButton {
                                    text: "保存"
                                }

                                ComButton {
                                    text: "测试连接"
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }
}
