import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend

import "./js/Common.js" as JSLib

Item {
    property StackView view
    property QmlService bgservice: null
    property bool loading: false

    id: page
    opacity: 0

    ComLoading {
        visible: parent.loading
    }

    ComDelay {
        id: delay
    }

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
                        if (sets.children[i] instanceof ComExpand) sets.children[i].unexpandF()
                    }
                }
            }

            ComButton {
                text: "展开全部"
                onClicked: {
                    for (let i in sets.children) {
                        if (sets.children[i] instanceof ComExpand) sets.children[i].expandF()
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

            Repeater {
                id: setsRepeater
                model: GlobalVariable.deviceList.length === GlobalVariable.maxDeviceCtn ? GlobalVariable.deviceList : 0

                ComExpand {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: `设备Id: ${modelData.dId} 设置项 - ${modelData.content}`
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
                                        onClicked: loadDSets(txtDeviceIp, txtDevicePort, modelData.dId)
                                    }

                                    ComButton {
                                        text: "保存"
                                        onClicked: saveDSets(txtDeviceIp, txtDevicePort, modelData.dId)
                                    }

                                    ComButton {
                                        text: "测试连接"
                                        onClicked: {
                                            loading = true
                                            delay.delay(100, () => {
                                                let ok = bgservice.testTcpConn(txtDeviceIp.text, parseInt(txtDevicePort.text))
                                                JSLib.showDialog(page, ok ? "提示" : "错误", `${txtDeviceIp.text} : ${txtDevicePort.text} ${ok ? "连接成功." : "连接失败."}`, ok ? "Info" : "Erro")
                                                loading = false
                                            })
                                        }
                                    }
                                }
                            }

                            Component.onCompleted: loadDSets(txtDeviceIp, txtDevicePort, modelData.dId)
                        }
                    }
                }
            }
        }
    }

    function loadDSets(txtIp, txtPort, dId) {
        GlobalVariable[`device${dId}Ip`] = txtIp.text = bgservice.takeSetting(`device${dId}Ip`)
        GlobalVariable[`device${dId}Port`] = txtPort.text = bgservice.takeSetting(`device${dId}Port`)
    }

    function saveDSets(txtIp, txtPort, dId) {
        bgservice.saveSettings(`device${dId}IP`, GlobalVariable[`device${dId}Ip`] = txtIp.text)
        bgservice.saveSettings(`device${dId}Port`, GlobalVariable[`device${dId}Port`] = txtPort.text)
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }
}
