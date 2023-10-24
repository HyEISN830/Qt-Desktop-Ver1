import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend
import DeviceBackend

import "./js/Common.js" as JSLib

Item {
    property StackView view
    property int panewide: 256

    id: page

    Row {
        anchors.fill: parent
        spacing: 8

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "blue"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "blue"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "blue"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "blue"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "blue"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            color: "blue"
        }
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }
}
