import QtQuick
import QtQuick.Controls

SplitView {
    id: rightPaneSplitView
    anchors.fill: parent
    handle: Rectangle {
        implicitWidth: 4
        implicitHeight: 4
        color: SplitHandle.pressed ? "#2c3e50"
            : (SplitHandle.hovered ? Qt.lighter("#bdc3c7", 1.1) : "#ecf0f1")
    }
}
