import QtQuick
import QtQuick.Controls

Item {
    property Component body: null   // content item, Component type required
    property bool ex: false // default expand status

    id: item
    height: expandItem.height + contentLoader.height
    width: 200

    Rectangle {
        property bool expand: false

        id: expandItem
        width: item.width
        height: 30
        color: "#ecf0f1"

        ColorAnimation {
            id: expandColorAni
            property: "color"
            target: expandItem
            from: "#ecf0f1"
            to: "#bdc3c7"
            duration: 200
        }

        ColorAnimation {
            id: unexpandColorAni
            property: "color"
            target: expandItem
            from: "#bdc3c7"
            to: "#ecf0f1"
            duration: 200
        }

        Image {
            id: arrow
            width: height
            height: parent.height
            source: "../resources/icon-arrow-right-fill.svg"

            RotationAnimation {
                id: expandAni
                target: arrow
                direction: RotationAnimation.Clockwise
                duration: 200
                from: 0
                to: 90
            }

            RotationAnimation {
                id: unexpandAni
                target: arrow
                direction: RotationAnimation.Counterclockwise
                duration: 200
                from: 90
                to: 0
            }
        }

        ComTextEditBold {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: arrow.right
            anchors.leftMargin: 3
            text: "Title Settings"
        }

        MouseArea {
            id: titleMArea
            property bool hovered: false

            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: parent.expand = !parent.expand
        }

        onExpandChanged: expand ? expandAni.start() + expandColorAni.start() + contentO1Ani.start() + contentHAni.start()
                                : unexpandAni.start() + unexpandColorAni.start() + contentO0Ani.start() + contentLAni.start()
    }

    Loader {
        id: contentLoader
        sourceComponent: body
        anchors.top: expandItem.bottom
        opacity: 0
        width: expandItem.width
    }

    OpacityAnimator {
        id: contentO1Ani
        target: contentLoader
        from: 0
        to: 1
        duration: 200
        easing.type: Easing.InOutQuad
    }

    OpacityAnimator {
        id: contentO0Ani
        target: contentLoader
        from: 1
        to: 0
        duration: 200
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        property real ch: 0

        id: contentHAni
        target: contentLoader
        from: 0
        to: ch
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }

    NumberAnimation {
        id: contentLAni
        target: contentLoader
        to: 0
        property: "height"
        duration: 200
        easing.type: Easing.InOutQuad
    }

    Component.onCompleted: {
        contentHAni.ch = contentLoader.height
        expandItem.expand = ex

        if (!ex)
            contentLAni.start()
    }

    function expandF() {
        expandItem.expand = true
    }

    function unexpandF() {
        expandItem.expand = false
    }
}
