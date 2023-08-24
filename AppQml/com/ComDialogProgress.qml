import QtQuick
import QtQuick.Controls

Popup {
    property real from: 0.0
    property real to: 1.0
    property real value: 0.0
    property string text: ""
    property int autoCloseDelay: 0
    property int timeoutClose: 30000    // 默认进度条无响应30s之后关闭, 无论何种情况

    id: popup
    padding: 10
    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.NoAutoClose
    modal: true
    contentItem: Rectangle {
        BusyIndicator {
            id: busyIndicator
            width: 60
            height: 60
            anchors.horizontalCenter: parent.horizontalCenter
            y: (parent.height / 2) - 45
            visible: value != to
        }
        Image {
            id: dialogImage
            width: 60
            height: 60
            mipmap: true
            source: "../resources/icon-success-green.svg"
            anchors.horizontalCenter: parent.horizontalCenter
            y: (parent.height / 2) - 45
            visible: value == to
        }
        ProgressBar {
            id: progress
            anchors.top: busyIndicator.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: busyIndicator.horizontalCenter
            from: popup.from
            to: popup.to
            value: popup.value
            onValueChanged: {
                delay.cancel()
                delay.delay(timeoutClose, () => { close() })
                if (value == to && autoCloseDelay) {

                    delay.delay(autoCloseDelay, () => { popup.close() })
                }
            }
        }
        ComTextEdit {
            anchors.bottom: progress.top
            anchors.bottomMargin: 5
            anchors.right: progress.right
            anchors.rightMargin: 10
            text: qsTr(`${value} / ${to}`)
        }
        ComTextEdit {
            anchors.top: progress.bottom
            anchors.topMargin: 5
            anchors.horizontalCenter: progress.horizontalCenter
            text: qsTr(popup.text)
        }
    }
    background: Rectangle {
        radius: height / 4
        anchors.centerIn: parent
        color: "White"
        width: 230
        height: 200
    }
    Overlay.modal: Rectangle {
        color: "#94c3c3c3"
    }

    ComDelay {
        id: delay
    }

    function openWith(f, t, v, c = "") {
        delay.cancel()
        delay.delay(timeoutClose, () => { close() })
        popup.from = f
        popup.to = t
        popup.value = v
        popup.text = c
        popup.open()
    }
}
