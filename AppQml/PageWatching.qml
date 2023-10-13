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
    property list<ComDevice> deviceList: [
        plc,
        plc1,
        cam,
        cam1,
        cam2,
        cam3,
        cam4,
        cam5,
        arm,
        arm1,
        arm2,
        arm3,
        arm4,
        arm5,
        agv
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
                onFinished: plc1YAni.start()
            }
        }

        ComDevice {
            id: plc1
            x: plc.x + plc.width + 30
            y: 18
            dId: 2
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "线体PLC2"
            iconPath: "resources/plc.png"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: plc1SAni
                target: plc1
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: plc1HAni
                target: plc1
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: plc1YAni
                target: plc1
                property: "y"
                duration: 200
                from: 50
                to: 18
                easing.type: Easing.InOutQuad
                onStarted: plc1SAni.start()
            }
        }

        ComDevice {
            x: 35
            y: 118
            id: cam
            dId: 3
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "W1扫码枪"
            iconPath: "resources/barcode-scan.png"
            iconColor: "#815f5166"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: camSAni
                target: cam
                from: 0
                to: 1
                duration: 500
                running: view.currentItem == page
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: camHAni
                target: cam
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: camYAni
                target: cam
                property: "y"
                duration: 200
                from: 168
                to: 118
                easing.type: Easing.InOutQuad
                running: view.currentItem == page
                onFinished: cam1YAni.start()
            }
        }

        ComDevice {
            id: cam1
            x: cam.x + cam.width + 30
            y: 118
            dId: 4
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "W2扫码枪"
            iconPath: "resources/barcode-scan.png"
            iconColor: "#815f5166"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: cam1SAni
                target: cam1
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: cam1HAni
                target: cam1
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: cam1YAni
                target: cam1
                property: "y"
                duration: 200
                from: 168
                to: 118
                easing.type: Easing.InOutQuad
                onStarted: cam1SAni.start()
                onFinished: cam2YAni.start()
            }
        }

        ComDevice {
            id: cam2
            x: cam1.x + cam1.width + 30
            y: 118
            dId: 5
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "W3扫码枪"
            iconPath: "resources/barcode-scan.png"
            iconColor: "#815f5166"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: cam2SAni
                target: cam2
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: cam2HAni
                target: cam2
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: cam2YAni
                target: cam2
                property: "y"
                duration: 200
                from: 168
                to: 118
                easing.type: Easing.InOutQuad
                onStarted: cam2SAni.start()
                onFinished: cam3YAni.start()
            }
        }

        ComDevice {
            id: cam3
            x: cam2.x + cam2.width + 30
            y: 118
            dId: 6
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "N1扫码枪"
            iconPath: "resources/barcode-scan.png"
            iconColor: "#815f5166"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: cam3SAni
                target: cam3
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: cam3HAni
                target: cam3
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: cam3YAni
                target: cam3
                property: "y"
                duration: 200
                from: 168
                to: 118
                easing.type: Easing.InOutQuad
                onStarted: cam3SAni.start()
                onFinished: cam4YAni.start()
            }
        }

        ComDevice {
            id: cam4
            x: 35
            y: 118
            dId: 7
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "N2扫码枪"
            iconPath: "resources/barcode-scan.png"
            iconColor: "#815f5166"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: cam4SAni
                target: cam4
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: cam4HAni
                target: cam4
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: cam4YAni
                target: cam4
                property: "y"
                duration: 200
                from: 268
                to: 218
                easing.type: Easing.InOutQuad
                onStarted: cam4SAni.start()
                onFinished: cam5YAni.start()
            }
        }

        ComDevice {
            id: cam5
            x: cam4.x + cam4.width + 30
            y: 118
            dId: 8
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "N3扫码枪"
            iconPath: "resources/barcode-scan.png"
            iconColor: "#815f5166"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: cam5SAni
                target: cam5
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: cam5HAni
                target: cam5
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: cam5YAni
                target: cam5
                property: "y"
                duration: 200
                from: 268
                to: 218
                easing.type: Easing.InOutQuad
                onStarted: cam5SAni.start()
            }
        }

        ComDevice {
            id: agv
            x: 35
            y: 518
            dId: 9
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "SJ AGV"
            iconPath: "resources/agv-robot.png"
            iconColor: "#7effd15b"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: agvSAni
                target: agv
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
                running: view.currentItem == page
            }

            OpacityAnimator {
                id: agvHAni
                target: agv
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: agvYAni
                target: agv
                property: "y"
                duration: 200
                from: 568
                to: 518
                easing.type: Easing.InOutQuad
                onStarted: agvSAni.start()
            }
        }

        ComDevice {
            id: arm
            x: 35
            y: 318
            dId: 10
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "W1机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: armSAni
                target: arm
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
                running: view.currentItem == page
            }

            OpacityAnimator {
                id: armHAni
                target: arm
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: armYAni
                target: arm
                property: "y"
                duration: 200
                from: 368
                to: 318
                easing.type: Easing.InOutQuad
                running: view.currentItem == page
                onStarted: armSAni.start()
                onFinished: arm1YAni.start()
            }
        }

        ComDevice {
            id: arm1
            x: arm.x + arm.width + 30
            y: 318
            dId: 11
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "W2机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: arm1SAni
                target: arm1
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: arm1HAni
                target: arm1
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: arm1YAni
                target: arm1
                property: "y"
                duration: 200
                from: 368
                to: 318
                easing.type: Easing.InOutQuad
                onStarted: arm1SAni.start()
                onFinished: arm2YAni.start()
            }
        }

        ComDevice {
            id: arm2
            x: arm1.x + arm1.width + 30
            y: 318
            dId: 12
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "W3机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: arm2SAni
                target: arm2
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: arm2HAni
                target: arm2
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: arm2YAni
                target: arm2
                property: "y"
                duration: 200
                from: 368
                to: 318
                easing.type: Easing.InOutQuad
                onStarted: arm2SAni.start()
                onFinished: arm3YAni.start()
            }
        }

        ComDevice {
            id: arm3
            x: arm2.x + arm2.width + 30
            y: 318
            dId: 13
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "N1机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: arm3SAni
                target: arm3
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: arm3HAni
                target: arm3
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: arm3YAni
                target: arm3
                property: "y"
                duration: 200
                from: 368
                to: 318
                easing.type: Easing.InOutQuad
                onStarted: arm3SAni.start()
                onFinished: arm4YAni.start()
            }
        }

        ComDevice {
            id: arm4
            x: 35
            y: 418
            dId: 14
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "N2机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: arm4SAni
                target: arm4
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: arm4HAni
                target: arm4
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: arm4YAni
                target: arm4
                property: "y"
                duration: 200
                from: 468
                to: 418
                easing.type: Easing.InOutQuad
                onStarted: arm4SAni.start()
                onFinished: arm5YAni.start()
            }
        }

        ComDevice {
            id: arm5
            x: arm4.x + arm4.width + 30
            y: 418
            dId: 15
            title: GlobalVariable[`device${dId}Ip`]
            opacity: 0
            content: "N3机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: GlobalVariable[`device${dId}Connected`]

            OpacityAnimator {
                id: arm5SAni
                target: arm5
                from: 0
                to: 1
                duration: 500
                easing.type: Easing.InOutQuad
            }

            OpacityAnimator {
                id: arm5HAni
                target: arm5
                from: 1
                to: 0
                duration: 10
                running: view.currentItem != page
                easing.type: Easing.InOutQuad
            }

            NumberAnimation {
                id: arm5YAni
                target: arm5
                property: "y"
                duration: 200
                from: 468
                to: 418
                easing.type: Easing.InOutQuad
                onStarted: arm5SAni.start()
            }
        }
    }

    Component.onCompleted: {
        GlobalVariable.maxDeviceCtn = deviceList.length
        for (let i in deviceList) {
            GlobalVariable.deviceList.push(deviceList[i])
            GlobalVariable.deviceMap[deviceList[i].dId] = deviceList[i]
        }

        delay.delay(1000, () => {
            deviceCenter.addplc(1, GlobalVariable["device1Ip"], GlobalVariable["device1Port"], GlobalEnums.LineNo.All, [GlobalEnums.LineNo.All])

            // W1 line devices
            deviceCenter.addscanner(3, GlobalVariable["device3Ip"], GlobalVariable["device3Port"], GlobalEnums.LineNo.W1)
            deviceCenter.addrobot(10, GlobalVariable["device10Ip"], GlobalVariable["device10Port"], GlobalEnums.LineNo.W1)

            // W2 line devices
            deviceCenter.addscanner(4, GlobalVariable["device4Ip"], GlobalVariable["device4Port"], GlobalEnums.LineNo.W2)
            deviceCenter.addrobot(11, GlobalVariable["device11Ip"], GlobalVariable["device11Port"], GlobalEnums.LineNo.W2)

            // W3 line devices
            deviceCenter.addscanner(5, GlobalVariable["device5Ip"], GlobalVariable["device5Port"], GlobalEnums.LineNo.W3)
            deviceCenter.addrobot(12, GlobalVariable["device12Ip"], GlobalVariable["device12Port"], GlobalEnums.LineNo.W3)

            // N3 line devices
            deviceCenter.addscanner(8, GlobalVariable["device8Ip"], GlobalVariable["device8Port"], GlobalEnums.LineNo.N3)
            deviceCenter.addrobot(15, GlobalVariable["device15Ip"], GlobalVariable["device15Port"], GlobalEnums.LineNo.N3)

            // N2 line devices
            deviceCenter.addscanner(7, GlobalVariable["device7Ip"], GlobalVariable["device7Port"], GlobalEnums.LineNo.N2)
            deviceCenter.addrobot(14, GlobalVariable["device14Ip"], GlobalVariable["device14Port"], GlobalEnums.LineNo.N2)

            // N1 line devices
            deviceCenter.addscanner(6, GlobalVariable["device6Ip"], GlobalVariable["device6Port"], GlobalEnums.LineNo.N1)
            deviceCenter.addrobot(13, GlobalVariable["device13Ip"], GlobalVariable["device13Port"], GlobalEnums.LineNo.N1)

            // start devicecenter
            deviceCenter.start()
        })
    }
}
