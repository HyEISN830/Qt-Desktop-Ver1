import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects
import AppQml
import AppQmlBackend
import DeviceBackend

import "./js/Common.js" as JSLib


Item {
    property StackView view
    property PageTLogs log
    property DeviceCenter deviceCenter
    property bool isCurPage: view.currentItem == page
    property list<ComDevice> deviceList: [
        a1,
        a2
    ]

    id: page
    opacity: 0

    ComDelay {
        id: delay
    }

    Connections {
        target: deviceCenter
        function onPathCalculated(id, path) {
            console.log(id, JSON.stringify(path))
        }
    }

    Pane {
        anchors.fill: parent
        padding: 0
        background: Rectangle {
            color: "#ecf0f1"
        }

        Column {
            spacing: 12
            leftPadding: 35
            topPadding: 20

            ComButton {
                text: "PATH"
                onClicked: {
                    deviceCenter.pathfinding_test(951, 0, 0, 4, 4, true)
                }
            }

            Row {
                spacing: 30

                ComDevice {
                    property string posi: "5xxx"
                    property string stat: "空闲"

                    id: agv950
                    dId: 1
                    title: "AGV-950"
                    content: `在${posi}-${stat}中`
                    iconPath: "resources/agv-robot.png"
                    connected: GlobalVariable[`device${dId}Connected`]
                }

                ComDevice {
                    property string posi: "5xxx"
                    property string stat: "空闲"

                    id: agv951
                    dId: 2
                    title: "AGV-951"
                    content: `在${posi}-${stat}中`
                    iconPath: "resources/agv-robot.png"
                    connected: GlobalVariable[`device${dId}Connected`]
                }

                ComDevice {
                    id: a1
                    dId: 1
                    title: GlobalVariable[`device${dId}Ip`]
                    opacity: 0
                    content: "AGV950"
                    iconPath: "resources/robotic-arm.png"
                    iconColor: "#80ffcd05"
                    connected: GlobalVariable[`device${dId}Connected`]
                }

                ComDevice {
                    id: a2
                    dId: 2
                    title: GlobalVariable[`device${dId}Ip`]
                    opacity: 0
                    content: "AGV951"
                    iconPath: "resources/robotic-arm.png"
                    iconColor: "#80ffcd05"
                    connected: GlobalVariable[`device${dId}Connected`]
                }
            }

            Row {
                spacing: 35

                ComGuassPane {
                    id: agv950pane
                    width: 170
                    height: 250

                    ComTextEditBold {
                        text: "AGV-950"
                        font.pixelSize: 18
                        topPadding: 8
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        width: parent.width / 2
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: 28
                        anchors.bottom: parent.bottom
                        color: "transparent"

                        Column {
                            topPadding: 8
                            leftPadding: 8
                            spacing: 8

                            ComTextEdit {
                                text: `当前电量:`
                            }
                            ComTextEdit {
                                text: `当前点位:`
                            }
                            ComTextEdit {
                                text: `当前角度:`
                            }
                            ComTextEdit {
                                text: `当前坐标X:`
                            }
                            ComTextEdit {
                                text: `当前坐标Y:`
                            }
                            ComTextEdit {
                                text: `当前状态:`
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width / 2
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width / 2
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 28
                        anchors.bottom: parent.bottom
                        color: "transparent"

                        Column {
                            topPadding: 8
                            leftPadding: 8
                            spacing: 8

                            Label {
                                property int b: 0
                                property string c: "white"
                                id: agv950b
                                text: `<font color=\"${c}\">${b}%</font>`
                                // onBChanged: {
                                //     if (b > 80)
                                //         c = "#27ae60"
                                //     else if (b > 50)
                                //         c = "#f39c12"
                                //     else if (b >= 0)
                                //         c = "#e74c3c"
                                // }
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv950p
                                text: `${b}`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv950d
                                text: `${b}°`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv950x
                                text: `${b}mm`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv950y
                                text: `${b}mm`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv950s
                                text: "未知状态"
                                onBChanged: reflushstat(agv950s, b)
                            }
                        }
                    }
                }

                ComGuassPane {
                    id: agv951pane
                    width: 170
                    height: 250

                    ComTextEditBold {
                        text: "AGV-951"
                        font.pixelSize: 18
                        topPadding: 8
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Rectangle {
                        width: parent.width / 2
                        anchors.left: parent.left
                        anchors.top: parent.top
                        anchors.topMargin: 28
                        anchors.bottom: parent.bottom
                        color: "transparent"

                        Column {
                            topPadding: 8
                            leftPadding: 8
                            spacing: 8

                            ComTextEdit {
                                text: `当前电量:`
                            }
                            ComTextEdit {
                                text: `当前点位:`
                            }
                            ComTextEdit {
                                text: `当前角度:`
                            }
                            ComTextEdit {
                                text: `当前坐标X:`
                            }
                            ComTextEdit {
                                text: `当前坐标Y:`
                            }
                            ComTextEdit {
                                text: `当前状态:`
                            }
                        }
                    }

                    Rectangle {
                        width: parent.width / 2
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width / 2
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.topMargin: 28
                        anchors.bottom: parent.bottom
                        color: "transparent"

                        Column {
                            topPadding: 8
                            leftPadding: 8
                            spacing: 8

                            Label {
                                property int b: 0
                                property string c: "white"
                                id: agv951b
                                text: `<font color=\"${c}\">${b}%</font>`
                                // onBChanged: {
                                //     if (b > 80)
                                //         c = "#27ae60"
                                //     else if (b > 50)
                                //         c = "#f39c12"
                                //     else if (b >= 0)
                                //         c = "#e74c3c"
                                // }
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv951p
                                text: `${b}`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv951d
                                text: `${b}°`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv951x
                                text: `${b}mm`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv951y
                                text: `${b}mm`
                            }
                            ComTextEdit {
                                property int b: 0
                                id: agv951s
                                text: "未知状态"
                                onBChanged: reflushstat(agv951s, b)
                            }
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: deviceCenter
        function onRobotReceived_b(dId, bs) {
            let bytes = bgservice.bytes2jarr(bs)
            if (bytes[1] === 2) {   // agv status api
                let battery = bytes[3]
                let degree = bgservice.bytes2int(bytes[4], bytes[5])
                let posx = bgservice.bytes2int(bytes[6], bytes[7], bytes[8], bytes[9])
                let posy = bgservice.bytes2int(bytes[10], bytes[11], bytes[12], bytes[13])
                let status = bytes[14]
                let p = bgservice.bytes2uint(bytes[15], bytes[16])

                if (dId === 1) {
                    agv950b.b = battery
                    agv950d.b = degree
                    agv950x.b = posx
                    agv950y.b = posy
                    agv950s.b = status
                    agv950p.b = p
                }
                else if (dId  === 2) {
                    agv951b.b = battery
                    agv951d.b = degree
                    agv951x.b = posx
                    agv951y.b = posy
                    agv951s.b = status
                    agv951p.b = p
                }
            }
        }
    }

    // use only in line settings
    function setChange(key, value) {
        bgservice.saveSettings(key, value + "")
    }

    function reflushstat(comp, stat) {
        console.log(stat)
        if (stat === 1)  comp.text = "任务完成"
        else if (stat === 2)  comp.text = "任务执行中"
        else if (stat === 3)  comp.text = "任务异常"
        else if (stat === 4)  comp.text = "任务空闲"
        else if (stat === 5)  comp.text = "机器人暂停"
        else if (stat === 6)  comp.text = "举升货架状态"
        else if (stat === 7)  comp.text = "充电状态"
        else if (stat === 8)  comp.text = "弧线行走中"
        else if (stat === 9)  comp.text = "充满维护"
        else if (stat === 11) comp.text = "背货未识别"
        else if (stat === 12) comp.text = "货架偏角过大"
        else if (stat === 13) comp.text = "运动库异常"
        else if (stat === 14) comp.text = "货码无法识别"
        else if (stat === 15) comp.text = "货码不匹配"
        else if (stat === 16) comp.text = "举升异常"
        else if (stat === 17) comp.text = "充电桩异常"
        else if (stat === 18) comp.text = "电量无增加"
        else if (stat === 20) comp.text = "充电指令角度错误"
        else if (stat === 21) comp.text = "平台下发指令错误"
        else if (stat === 23) comp.text = "外力下放"
        else if (stat === 24) comp.text = "货架位置偏移"
        else if (stat === 25) comp.text = "小车不在锁定区"
        else if (stat === 26) comp.text = "下放重试失败"
        else if (stat === 27) comp.text = "货架摆歪"
        else if (stat === 28) comp.text = "举升电池电量太低"
        else if (stat === 29) comp.text = "后退角度偏大"
        else if (stat === 30) comp.text = "未背货架举升"
        else if (stat === 31) comp.text = "区域锁定失败"
        else if (stat === 33) comp.text = "旋转申请暂时失败"
        else if (stat === 34) comp.text = "地图切换点地码未识别"
        else comp.text = "未知状态"
    }

    Component.onCompleted: {
        GlobalVariable.maxDeviceCtn = deviceList.length
        for (let i in deviceList) {
            GlobalVariable.deviceList.push(deviceList[i])
            GlobalVariable.deviceMap[deviceList[i].dId] = deviceList[i]
        }

        delay.delay(1000, () => {
            deviceCenter.addrobot(1, GlobalVariable["device1Ip"], GlobalVariable["device1Port"], GlobalEnums.LineNo.All)
            deviceCenter.addrobot(2, GlobalVariable["device2Ip"], GlobalVariable["device2Port"], GlobalEnums.LineNo.All)

            // start devicecenter
            deviceCenter.start()
        })
    }
}
