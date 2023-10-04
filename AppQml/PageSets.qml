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
                                        width: lblURL.width + txtURL.width
                                        height: txtURL.height

                                        ComLabel {
                                            id: lblURL
                                            anchors.verticalCenter: txtURL.verticalCenter
                                            text: "IP: "
                                        }

                                        ComTextField {
                                            id: txtURL
                                            anchors.left: lblURL.right
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
                                        onClicked: loadDSets(txtURL, txtDevicePort, modelData.dId)
                                    }

                                    Rectangle {
                                        color: "transparent"
                                        width: btnSave.width
                                        height: btnSave.height

                                        ComButton {
                                            id: btnSave
                                            text: "保存"
                                            onClicked: {
                                                saveDSets(txtURL, txtDevicePort, modelData.dId)
                                                btnSaveIconShowAni.start()
                                            }
                                            opacity: 1
                                        }

                                        Image {
                                            id: btnSaveIcon
                                            anchors.centerIn: btnSave
                                            source: "resources/icon-success-green.svg"
                                            width: 40
                                            height: 40
                                            mipmap: true
                                            opacity: 0

                                            SequentialAnimation {
                                                id: btnSaveIconShowAni
                                                onStarted: btnSave.opacity = 0
                                                onFinished: btnSave.opacity = 1

                                                OpacityAnimator {
                                                    target: btnSaveIcon
                                                    from: 0
                                                    to: 1
                                                    duration: 700
                                                    easing.type: Easing.InOutCubic
                                                }

                                                OpacityAnimator {
                                                    target: btnSaveIcon
                                                    from: 1
                                                    to: 0
                                                    duration: 500
                                                    easing.type: Easing.OutCubic
                                                }
                                            }
                                        }
                                    }

                                    ComButton {
                                        text: "测试连接"
                                        visible: false
                                        onClicked: {
                                            loading = true
                                            delay.delay(100, () => {
                                                let ok = bgservice.testTcpConn(txtURL.text, parseInt(txtDevicePort.text))
                                                JSLib.showDialog(page, ok ? "提示" : "错误", `${txtURL.text} : ${txtDevicePort.text} ${ok ? "连接成功." : "连接失败."}`, ok ? "Info" : "Erro")
                                                loading = false
                                            })
                                        }
                                    }
                                }
                            }

                            Component.onCompleted: loadDSets(txtURL, txtDevicePort, modelData.dId)
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `条码信息接口 设置项`
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
                                    width: lblURL.width + txtURL.width
                                    height: txtURL.height

                                    ComLabel {
                                        id: lblURL
                                        anchors.verticalCenter: txtURL.verticalCenter
                                        text: "URL: "
                                    }

                                    ComTextField {
                                        id: txtURL
                                        anchors.left: lblURL.right
                                        placeholderText: "URL"
                                        width: 900
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtURL, "barcodeInfoURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtURL, "barcodeInfoURL")
                                            btnSaveIconShowAni.start()
                                        }
                                        opacity: 1
                                    }

                                    Image {
                                        id: btnSaveIcon
                                        anchors.centerIn: btnSave
                                        source: "resources/icon-success-green.svg"
                                        width: 40
                                        height: 40
                                        mipmap: true
                                        opacity: 0

                                        SequentialAnimation {
                                            id: btnSaveIconShowAni
                                            onStarted: btnSave.opacity = 0
                                            onFinished: btnSave.opacity = 1

                                            OpacityAnimator {
                                                target: btnSaveIcon
                                                from: 0
                                                to: 1
                                                duration: 700
                                                easing.type: Easing.InOutCubic
                                            }

                                            OpacityAnimator {
                                                target: btnSaveIcon
                                                from: 1
                                                to: 0
                                                duration: 500
                                                easing.type: Easing.OutCubic
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Component.onCompleted: loadUSets(txtURL, "barcodeInfoURL")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `板栈信息上传接口 设置项`
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
                                    width: lblURL.width + txtURL.width
                                    height: txtURL.height

                                    ComLabel {
                                        id: lblURL
                                        anchors.verticalCenter: txtURL.verticalCenter
                                        text: "URL: "
                                    }

                                    ComTextField {
                                        id: txtURL
                                        anchors.left: lblURL.right
                                        placeholderText: "URL"
                                        width: 900
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtURL, "stackUploadURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtURL, "stackUploadURL")
                                            btnSaveIconShowAni.start()
                                        }
                                        opacity: 1
                                    }

                                    Image {
                                        id: btnSaveIcon
                                        anchors.centerIn: btnSave
                                        source: "resources/icon-success-green.svg"
                                        width: 40
                                        height: 40
                                        mipmap: true
                                        opacity: 0

                                        SequentialAnimation {
                                            id: btnSaveIconShowAni
                                            onStarted: btnSave.opacity = 0
                                            onFinished: btnSave.opacity = 1

                                            OpacityAnimator {
                                                target: btnSaveIcon
                                                from: 0
                                                to: 1
                                                duration: 700
                                                easing.type: Easing.InOutCubic
                                            }

                                            OpacityAnimator {
                                                target: btnSaveIcon
                                                from: 1
                                                to: 0
                                                duration: 500
                                                easing.type: Easing.OutCubic
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Component.onCompleted: loadUSets(txtURL, "stackUploadURL")
                    }
                }
            }
        }
    }

    function loadDSets(txtIp, txtPort, dId) {
        GlobalVariable[`device${dId}Ip`] = txtIp.text = bgservice.takeSetting(`device${dId}Ip`)
        GlobalVariable[`device${dId}Port`] = txtPort.text = bgservice.takeSetting(`device${dId}Port`)
    }

    function loadUSets(txtURL, name) {
        txtURL.text = bgservice.takeSetting(name)
    }

    function saveDSets(txtIp, txtPort, dId) {
        bgservice.saveSettings(`device${dId}IP`, GlobalVariable[`device${dId}Ip`] = txtIp.text)
        bgservice.saveSettings(`device${dId}Port`, GlobalVariable[`device${dId}Port`] = txtPort.text)
    }

    function saveUSets(txtURL, name) {
        bgservice.saveSettings(name, txtURL.text)
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }
}
