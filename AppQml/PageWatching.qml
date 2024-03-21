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
            ComButton {
                text: "PATH"
                onClicked: {
                    deviceCenter.pathfinding_test(951, 0, 0, 4, 4, true)
                }
            }
        }
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
            // start devicecenter
            deviceCenter.start()
        })
    }
}
