import QtQuick
import Qt5Compat.GraphicalEffects


Rectangle {
    property string c: "#763498db"

    id: root
    color: "transparent"

    Rectangle {
        id: b
        width: parent.width
        height: parent.height
        radius: 10
        color: c
    }

    FastBlur {
        anchors.fill: b
        source: b
        radius: 64
        transparentBorder: true
    }
}
