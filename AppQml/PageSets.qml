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
                title: `Upload Matl - Setting`
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
                                    onClicked: loadUSets(txtLength, "uploadMatlURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "uploadMatlURL")
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

                        Component.onCompleted: loadUSets(txtLength, "uploadMatlURL")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `Pull Up Matl - Setting`
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
                                    onClicked: loadUSets(txtLength, "pullUpMatlURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "pullUpMatlURL")
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

                        Component.onCompleted: loadUSets(txtLength, "pullUpMatlURL")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `Commit Stacks - Setting`
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
                                    onClicked: loadUSets(txtLength, "commitStacksURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "commitStacksURL")
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

                        Component.onCompleted: loadUSets(txtLength, "commitStacksURL")
                    }
                }
            }

            ComExpand {
                anchors.left: parent.left
                anchors.right: parent.right
                title: `Robot Params - Setting`
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
                                    onClicked: loadUSets(txtLength, "robotParamsURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "robotParamsURL")
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

                        Component.onCompleted: loadUSets(txtLength, "robotParamsURL")
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
                title: `CStack - Setting`
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
                                    onClicked: loadUSets(txtLength, "cstackURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "cstackURL")
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

                        Component.onCompleted: loadUSets(txtLength, "cstackURL")
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
                                    onClicked: loadUSets(txtLength, "barcodeInfoURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "barcodeInfoURL")
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

                        Component.onCompleted: loadUSets(txtLength, "barcodeInfoURL")
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
                                    onClicked: loadUSets(txtLength, "stackUploadURL")
                                }

                                Rectangle {
                                    color: "transparent"
                                    width: btnSave.width
                                    height: btnSave.height

                                    ComButton {
                                        id: btnSave
                                        text: "保存"
                                        onClicked: {
                                            saveUSets(txtLength, "stackUploadURL")
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

                        Component.onCompleted: loadUSets(txtLength, "stackUploadURL")
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
