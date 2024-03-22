import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend
import DeviceBackend

import "./js/Common.js" as JSLib


Item {
    property StackView view
    property PageTLogs log
    property DeviceCenter deviceCenter
    property QmlService bgservice
    property bool isCurPage: view.currentItem == page
    property list<ComDevice> deviceList: [
        plc,
        scheduling,
    ]

    id: page
    opacity: 0

    ComDelay {
        id: delay
    }

    Timer {
        id: plc_polling
        interval: 500
        running: true
        repeat: true
        onTriggered: {
            updRegisters(deviceCenter.getPlcRegisters(1))
        }
    }

    Pane {
        padding: 0
        anchors.fill: parent
        background: Rectangle {
            color: "#ecf0f1"
        }

        ComDevice {
            x: 35
            y: 18
            id: plc
            dId: 1
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "线体PLC1"
            iconPath: "resources/plc.png"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: plcSAni
                target: plc
                from: 0
                to: 1
                duration: 500
                running: view.currentItem == page
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: plcHAni
                target: plc
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: plcYAni
                target: plc
                property: "y"
                duration: 200
                from: 50
                to: 18
                easing.type: Easing.InOutQuad
                running: view.currentItem == page
                onFinished: schedulingYAni.start()
            }
        }

        ComDevice {
            id: scheduling
            x: plc.x + plc.width + 30
            y: 18
            dId: 2
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "调度任务订阅"
            iconPath: "resources/task.png"
            iconColor: "#A8DBA8"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: schedulingSAni
                target: scheduling
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: schedulingHAni
                target: scheduling
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: schedulingYAni
                target: scheduling
                property: "y"
                duration: 200
                from: 50
                to: 18
                easing.type: Easing.InOutQuad
                onStarted: schedulingSAni.start()
            }
        }

        Column {
            topPadding: 130
            leftPadding: 35
            padding: 20

            ComLabel {
               property string bc: ""

               id: curbarcode
               bottomPadding: 10
               font.pixelSize: 20
               text: `当前条码: <font color="#f39c12">${bc}</font>`
            }

            Row {
                spacing: 8

                ComLabel {
                    property int idle: -1
                    property string c: idle ? "#2ecc71" : "#e74c3c"

                    id: s001stat
                    font.pixelSize: 20
                    text: `S001(CTU上料码头)状态: <font color="${c}">${idle ? "空闲" : "非空闲"}</font>`
                }

                ComButton {
                    id: ctudrop
                    anchors.verticalCenter: s001stat.verticalCenter
                    text: "CTU上料完成"
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs001ready"), 1)
                }

                ComButton {
                    text: "<font color=\"#e74c3c\">复位</font>"
                    anchors.verticalCenter: s001stat.verticalCenter
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs001ready"), 0)
                }
            }

            Row {
                spacing: 8

                ComLabel {
                    property int idle: -1
                    property string c: idle ? "#2ecc71" : "#e74c3c"

                    id: s004stat
                    font.pixelSize: 20
                    text: `S004(扫码处物料)状态: <font color="${c}">${idle ? "有料" : "无料"}</font>`
                }

                ComButton {
                    id: gotopull
                    anchors.verticalCenter: s004stat.verticalCenter
                    text: "分流去取料点"
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs004shunt"), 1)
                }

                ComButton {
                    id: gotopick
                    anchors.verticalCenter: s004stat.verticalCenter
                    text: "分流去拣货点"
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs004shunt"), 2)
                }

                ComButton {
                    anchors.verticalCenter: s004stat.verticalCenter
                    text: "<font color=\"#e74c3c\">复位</font>"
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs004shunt"), 0)
                }
            }

            Row {
                spacing: 8

                ComLabel {
                    property int idle: -1
                    property string c: idle ? "#2ecc71" : "#e74c3c"

                    id: s006stat
                    font.pixelSize: 20
                    text: `S006(CTU取料码头)状态: <font color="${c}">${idle ? "有料" : "无料"}</font>`
                }

                ComButton {
                    id: ctupull
                    anchors.verticalCenter: s006stat.verticalCenter
                    text: "CTU取料完成"
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs006ready"), 1)
                }

                ComButton {
                    anchors.verticalCenter: s006stat.verticalCenter
                    text: "<font color=\"#e74c3c\">复位</font>"
                    onClicked: deviceCenter.writePlcRegister(1, 1, bgservice.itakeSetting("plcs006ready"), 0)
                }
            }
        }
    }


    function updRegisters(registers) {
        let barr = []

        for (let i = bgservice.itakeSetting("plcbarcodeaddr"); i < 17; i++)
            barr.push(registers[i])

        curbarcode.bc = bgservice.bytes2String(barr)
        s001stat.idle = registers[bgservice.itakeSetting("plcs001stat")]
        s004stat.idle = registers[bgservice.itakeSetting("plcs004stat")]
        s006stat.idle = registers[bgservice.itakeSetting("plcs006stat")]
    }

    // use only in line settings
    function setChange(key, value) {
        bgservice.saveSettings(key, value + "")
    }

    Component.onCompleted: {
        GlobalVariable.maxDeviceCtn = deviceList.length
        for (let i in deviceList) {
            GlobalVariable.deviceList.push(deviceList[i])
            GlobalVariable.deviceMap[deviceList[i].dId] = deviceList[i]
        }

        delay.delay(1000, () => {
            deviceCenter.addplc(1, GlobalVariable["device1Ip"], GlobalVariable["device1Port"], GlobalEnums.LineNo.All, [GlobalEnums.LineNo.All])

            // start devicecenter
            deviceCenter.start()
        })
    }
}
