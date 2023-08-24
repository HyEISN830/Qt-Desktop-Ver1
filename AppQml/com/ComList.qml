import QtQuick
import QtQuick.Controls

ListView {
    id: leftPaneListView
    anchors.fill: parent
    anchors.topMargin: 22
    anchors.bottomMargin: 30
    boundsMovement: Flickable.StopAtBounds
    boundsBehavior: Flickable.DragOverBounds
    cacheBuffer: 0
    highlightResizeVelocity: 0
    interactive: true
    layer.smooth: true
    ScrollBar.vertical: ScrollBar { }
    add: Transition {
        NumberAnimation {
            properties: "x"
            from: 50
            duration: 300
        }
    }
    model: ListModel {
    }
}

