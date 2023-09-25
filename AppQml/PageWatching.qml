import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend
import DeviceBackend


Item {
    property StackView view
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

    DeviceCenter {
        id: deviceCenter
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
            title: "0.0.0.0"
            opacity: 0
            content: "W1机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: false

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
            title: "0.0.0.0"
            opacity: 0
            content: "W2机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: false

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
            title: "0.0.0.0"
            opacity: 0
            content: "W3机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: false

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
            title: "0.0.0.0"
            opacity: 0
            content: "N1机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: false

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
            title: "0.0.0.0"
            opacity: 0
            content: "N2机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: false

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
            title: "0.0.0.0"
            opacity: 0
            content: "N3机械臂"
            iconPath: "resources/robotic-arm.png"
            iconColor: "#80ffcd05"
            connected: false

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

        Column {
            x: 35
            y: 700
            visible: true

            Row {
                spacing: 30
            }

            Row {
                spacing: 8

                ComButton {
                    text:  "rx"
                    onClicked: plc.rx()
                }

                ComButton {
                    text:  "tx"
                    onClicked: plc.tx()
                }

                ComButton {
                    property bool conn: false

                    text: "conn"
                    onClicked: GlobalVariable.deviceConnected = !GlobalVariable.deviceConnected
                }
            }
        }
    }

    Component.onCompleted: {
        GlobalVariable.maxDeviceCtn = deviceList.length
        for (let i in deviceList)
            GlobalVariable.deviceList.push(deviceList[i])

        delay.delay(3000, () => {
            deviceCenter.addscanner(3, GlobalVariable["device3Ip"], GlobalVariable["device3Port"], GlobalEnums.LineNo.W1)

            // start devicecenter loop
            deviceCenter.start()
        })
    }

//    onIsCurPageChanged: function () {
//        if (!isCurPage) {
//            // when quicky swap pages, complete all animations
////            plcSAni.complete()
//            plcHAni.complete()
//            plcYAni.complete()
////            plc1SAni.complete()
//            plc1HAni.complete()
//            plc1YAni.complete()
////            camSAni.complete()
//            camHAni.complete()
//            camYAni.complete()
////            cam1SAni.complete()
//            cam1HAni.complete()
//            cam1YAni.complete()
////            cam2SAni.complete()
//            cam2HAni.complete()
//            cam2YAni.complete()
////            cam3SAni.complete()
//            cam3HAni.complete()
//            cam3YAni.complete()
////            cam4SAni.complete()
//            cam4HAni.complete()
//            cam4YAni.complete()
////            cam5SAni.complete()
//            cam5HAni.complete()
//            cam5YAni.complete()
//        }
//    }
}
