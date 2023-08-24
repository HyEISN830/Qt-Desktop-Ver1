import QtQuick
import QtQuick.Controls

Popup {
    id: popup
    padding: 10
    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.NoAutoClose
    modal : true

    contentItem: Rectangle {
        color: "transparent"
        BusyIndicator {
            id: busyIndicator
            width: 60
            height: 60
        }
    }
    background: Rectangle {
        color: "transparent"
    }
    Overlay.modal: Rectangle {
        color: "#94c3c3c3"
    }
}
