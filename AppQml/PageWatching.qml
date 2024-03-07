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
    property bool isCurPage: view.currentItem == page
    property list<var> deviceList: [
    ]
    property var dmap: ({})
    property list<var> positions:
    [
        [
            { id: 1, name: "上位机", ip: "Wait4Conn", port: 9004, icon: "resources/server.png", color: "#c17a8c98", type: "gateserver", agvCode: 2 },
        ],
        [
            { id: 2, no: 1, name: "北2门(1号门)", ip: "192.168.81.142", port: "502", icon: "resources/icon-gate.png", color: "#c2e8f7", type: "gatecli" },
            { id: 3, no: 2, name: "北1门(2号门)", ip: "192.168.81.143", port: "502", icon: "resources/icon-gate.png", color: "#c2e8f7", type: "gatecli" },
            { id: 4, no: 3, name: "焊接(3号门)", ip: "192.168.81.144", port: "502", icon: "resources/icon-gate.png", color: "#c2e8f7", type: "gatecli" },
            { id: 5, no: 4, name: "精密车间(4号门)", ip: "192.168.81.145", port: "502", icon: "resources/icon-gate.png", color: "#c2e8f7", type: "gatecli" },
        ]
    ]

    id: page
    opacity: 0

    ComDelay {
        id: delay
    }

    Pane {
        anchors.fill: parent
        padding: 0
        background: Rectangle {
            color: "#ecf0f1"
        }

        ScrollView {
            width: parent.width
            height: parent.height

            Column {
                spacing: 13

                Rectangle { // placeholder
                    width: 1
                    height: 10
                    color: "transparent"
                }

                Repeater {
                    model: positions

                    Row {
                        spacing: 25

                        Rectangle { // placeholder
                            height: 1
                            width: 10
                            color: "transparent"
                        }

                        Repeater {
                            model: modelData

                            ComDevice {
                                id: camrepeat
                                dId: modelData.id
                                title: modelData.ip
                                opacity: 0
                                content: modelData.name
                                iconPath: modelData.icon
                                iconColor: modelData.color
                                connected: false

                                OpacityAnimator {
                                    target: camrepeat
                                    from: 0
                                    to: 1
                                    duration: 500
                                    running: view.currentItem == page
                                    easing.type: Easing.InOutQuad
                                }

                                Component.onCompleted: {
                                    deviceList.push(camrepeat)
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    width: 1
                    height: 10
                    color: "transparent"
                }
            }
        }
    }

    // use only in line settings
    function setChange(key, value) {
        bgservice.saveSettings(key, value + "")
    }

    function setDIp(did, ip) {
        GlobalVariable.deviceMap[did].title = ip
    }

    function setDConn(did, connected) {
        GlobalVariable.deviceMap[did].connected = connected
    }

    function txd(did) {
        GlobalVariable.deviceMap[did].tx()
    }

    function rxd(did) {
        GlobalVariable.deviceMap[did].rx()
    }

    Connections {
        target: deviceCenter

        function onClientConnectIn(did, ip, port) {
            setDIp(did, ip)
            setDConn(did, true)
            log.appendSuccessLog(did, "已成功连接.")
        }

        function onClientConnectOut(did, ip, port) {
            setDIp(did, "Wait4Conn")
            setDConn(did, false)
            log.appendErrorLog(did, "连接已断开.")
        }

        function onDeviceReceived(did, data) {
            rxd(did)
            // log.appendNormalLog(did, `接收到 => <font color="#f1c40f">${JSON.stringify(data)}</font>`)
        }

        function onDeviceSended(did, data) {
            txd(did)
            // log.appendNormalLog(did, `发送到 => <font color="#f1c40f">${JSON.stringify(data)}</font>`)
        }

        function onDeviceConnected(did) {
            setDConn(did, true)
            log.appendSuccessLog(did, "已成功连接")
        }

        function onDeviceDisconnect(did) {
            setDConn(did, false)
            log.appendErrorLog(did, "连接已断开")
        }

        function onPointReceived(did, data) {
            rxd(did)
            log.appendNormalLog(did, `接收到 => <font color="#f1c40f">${JSON.stringify(data)}</font>`)
        }

        function onPointSended(did, data) {
            txd(did);
            // log.appendNormalLog(did, `发送到 => <font color="#f1c40f">${JSON.stringify(data)}</font>`)
        }

        function onSendCMD2(dId, no, data) {
            // txd(dId)
            // console.log(dId, no, data)
        }
    }

    Component.onCompleted: {
        for (let i in deviceList) {
            GlobalVariable.deviceList.push(deviceList[i])
            GlobalVariable.deviceMap[deviceList[i].dId] = deviceList[i]
        }

        delay.delay(3000, () => {
            for (let i1 in positions)
                for (let i2 in positions[i1])
                    if (positions[i1][i2].type === "client") deviceCenter.addpoint(positions[i1][i2].id, positions[i1][i2].ip, positions[i1][i2].port)
                    else if (positions[i1][i2].type === "server") deviceCenter.addserver(positions[i1][i2].id, positions[i1][i2].port, 1, positions[i1][i2].agvCode)
                    else if (positions[i1][i2].type === "gateserver") deviceCenter.addgateserver(positions[i1][i2].id, positions[i1][i2].port)
                    else if (positions[i1][i2].type === "gatecli") deviceCenter.addgateclient(positions[i1][i2].id, positions[i1][i2].no, positions[i1][i2].ip, positions[i1][i2].port)

            deviceCenter.start()
        })
    }
}
