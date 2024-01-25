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
            { id: 1, name: "上位机-AGV951", ip: "Wait4Conn", port: 8030, icon: "resources/server.png", color: "#c17a8c98", type: "server", agvCode: 2 },
            { id: 34, name: "上位机-AGV950", ip: "Wait4Conn", port: 8031, icon: "resources/server.png", color: "#c17a8c98", type: "server", agvCode: 1 },
        ],
        [
            { id: 2, name: "光通讯点位1", ip: "192.168.81.135", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 3, name: "光通讯点位2", ip: "192.168.81.134", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 4, name: "光通讯点位3", ip: "192.168.81.103", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 5, name: "光通讯点位4", ip: "192.168.81.104", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 6, name: "光通讯点位5", ip: "192.168.81.105", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 7, name: "光通讯点位6", ip: "192.168.81.106", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 8, name: "光通讯点位7", ip: "192.168.81.107", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 9, name: "光通讯点位8", ip: "192.168.81.108", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 10, name: "光通讯点位9", ip: "192.168.81.109", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 11, name: "光通讯点位10", ip: "192.168.81.110", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 12, name: "光通讯点位11", ip: "192.168.81.111", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 13, name: "光通讯点位12", ip: "192.168.81.112", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 14, name: "光通讯点位13", ip: "192.168.81.113", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 15, name: "光通讯点位14", ip: "192.168.81.114", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 16, name: "光通讯点位15", ip: "192.168.81.115", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 17, name: "光通讯点位16", ip: "192.168.81.116", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 18, name: "光通讯点位17", ip: "192.168.81.117", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 19, name: "光通讯点位18", ip: "192.168.81.118", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 20, name: "光通讯点位19", ip: "192.168.81.119", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 21, name: "光通讯点位20", ip: "192.168.81.120", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 22, name: "光通讯点位21", ip: "192.168.81.121", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 23, name: "光通讯点位22", ip: "192.168.81.122", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 24, name: "光通讯点位23", ip: "192.168.81.123", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 25, name: "光通讯点位24", ip: "192.168.81.124", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 26, name: "光通讯点位25", ip: "192.168.81.125", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 27, name: "光通讯点位26", ip: "192.168.81.126", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 28, name: "光通讯点位27", ip: "192.168.81.127", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 29, name: "光通讯点位28", ip: "192.168.81.128", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 30, name: "光通讯点位29", ip: "192.168.81.129", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 31, name: "光通讯点位30", ip: "192.168.81.130", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 32, name: "光通讯点位31", ip: "192.168.81.131", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            { id: 33, name: "光通讯点位32", ip: "192.168.81.132", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
        ],
        [
            { id: 35, name: "光通讯点位33", ip: "192.168.81.102", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            // { id: 98, name: "测试光通讯点位1", ip: "127.0.0.1", port: "8080", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
            // { id: 99, name: "测试光通讯点位2", ip: "127.0.0.1", port: "8081", icon: "resources/infrared.png", color: "#7f640000", type: "client" },
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

        function onClientReceived(did, data) {
            rxd(did)
            log.appendNormalLog(did, `接收到 => <font color="#f1c40f">${JSON.stringify(data)}</font>`)
        }

        function onClientSended(did, data) {
            txd(did)
            log.appendNormalLog(did, `发送到 => <font color="#f1c40f">${JSON.stringify(data)}</font>`)
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

            deviceCenter.start()
        })
    }
}
