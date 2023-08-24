import QtQuick
import QtQuick.Controls

Item {
    property StackView view

    id: page
    opacity: 0

    Label {
        text: qsTr("settings page")
        anchors.centerIn: parent
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }
}
