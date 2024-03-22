import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend
import DeviceBackend

import "./js/Common.js" as JSLib

Item {
    property StackView view
    property DeviceCenter deviceCenter
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
                                        width: lblLength.width + txtLength.width
                                        height: txtLength.height

                                        ComLabel {
                                            id: lblLength
                                            anchors.verticalCenter: txtLength.verticalCenter
                                            text: "IP: "
                                        }

                                        ComTextField {
                                            id: txtLength
                                            anchors.left: lblLength.right
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
                                        onClicked: loadDSets(txtLength, txtDevicePort, modelData.dId)
                                    }

                                    Rectangle {
                                        color: "transparent"
                                        width: btnSave.width
                                        height: btnSave.height

                                        ComButton {
                                            id: btnSave
                                            text: "保存"
                                            onClicked: {
                                                saveDSets(txtLength, txtDevicePort, modelData.dId)
                                                console.log(modelData.dId, txtLength.text, txtDevicePort.text)
                                                deviceCenter.reconnect(modelData.dId, txtLength.text, txtDevicePort.text)
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
                                                let ok = bgservice.testTcpConn(txtLength.text, parseInt(txtDevicePort.text))
                                                JSLib.showDialog(page, ok ? "提示" : "错误", `${txtLength.text} : ${txtDevicePort.text} ${ok ? "连接成功." : "连接失败."}`, ok ? "Info" : "Erro")
                                                loading = false
                                            })
                                        }
                                    }
                                }
                            }

                            Component.onCompleted: loadDSets(txtLength, txtDevicePort, modelData.dId)
                        }
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `App Log - Setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "URL: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
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
                                    onClicked: loadUSets(txtLength, "appLogURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "appLogURL")
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

                        Component.onCompleted: loadUSets(txtLength, "appLogURL")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `日志记录 设置项`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "最大长度: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "最大长度"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "logLength")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "logLength")
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

                        Component.onCompleted: loadUSets(txtLength, "logLength")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcs001stat - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcs001stat")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcs001stat")
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

                        Component.onCompleted: loadUSets(txtLength, "plcs001stat")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcs001ready - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcs001ready")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcs001ready")
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

                        Component.onCompleted: loadUSets(txtLength, "plcs001ready")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcbarcodeaddr - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcbarcodeaddr")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcbarcodeaddr")
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

                        Component.onCompleted: loadUSets(txtLength, "plcbarcodeaddr")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcs004stat - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcs004stat")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcs004stat")
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

                        Component.onCompleted: loadUSets(txtLength, "plcs004stat")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcs004shunt - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcs004shunt")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcs004shunt")
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

                        Component.onCompleted: loadUSets(txtLength, "plcs004shunt")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcs006stat - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcs006stat")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcs006stat")
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

                        Component.onCompleted: loadUSets(txtLength, "plcs006stat")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `plcs006ready - setting`
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
                                    width: lblLength.width + txtLength.width
                                    height: txtLength.height

                                    ComLabel {
                                        id: lblLength
                                        anchors.verticalCenter: txtLength.verticalCenter
                                        text: "addr: "
                                    }

                                    ComTextField {
                                        id: txtLength
                                        anchors.left: lblLength.right
                                        placeholderText: "addr"
                                        width: 100
                                    }
                                }
                            }

                            Row {
                                anchors.left: parent.left
                                anchors.right: parent.right
                                spacing: 8

                                ComButton {
                                    text: "重置"
                                    onClicked: loadUSets(txtLength, "plcs006ready")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "plcs006ready")
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

                        Component.onCompleted: loadUSets(txtLength, "plcs006ready")
                    }
                }
            }
        }
    }

    function loadDSets(txtIp, txtPort, dId) {
        GlobalVariable[`device${dId}Ip`] = txtIp.text = bgservice.takeSetting(`device${dId}Ip`)
        GlobalVariable[`device${dId}Port`] = txtPort.text = bgservice.takeSetting(`device${dId}Port`)
    }

    function loadUSets(txt, name) {
        txt.text = bgservice.takeSetting(name)
    }

    function saveDSets(txtIp, txtPort, dId) {
        bgservice.saveSettings(`device${dId}IP`, GlobalVariable[`device${dId}Ip`] = txtIp.text)
        bgservice.saveSettings(`device${dId}Port`, GlobalVariable[`device${dId}Port`] = txtPort.text)
    }

    function saveUSets(txt, name) {
        bgservice.saveSettings(name, txt.text)
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }
}
