import QtQuick
import QtQuick.Controls
import QtQuick.Shapes
import Qt5Compat.GraphicalEffects
import AppQml
import AppQmlBackend

Item {
    property StackView view

    id: page
    opacity: 0

    Image {
        id: img
        anchors.fill: parent
        source: "resources/home.jpg"
    }

    Image {
        id: img1
        property bool rounded: true
        property bool adapt: true

        anchors.top: rectBg1.top
        anchors.topMargin: 15
        anchors.left: rectBg1.left
        anchors.leftMargin: 15
        source: "resources/57463585_p6.png"
        width: 70
        height: 70
        mipmap: true
        visible: true
        z: 1
        layer.enabled: rounded
        layer.effect: OpacityMask {
            maskSource: Item {
                width: img1.width
                height: img1.height
                Rectangle {
                    anchors.centerIn: parent
                    width: img1.adapt ? img1.width : Math.min(img1.width, img1.height)
                    height: img1.adapt ? img1.height : width
                    radius: Math.min(width, height)
                }
            }
        }
    }

    Rectangle {
        id: rectBg1
        color: "#7dced6e0"
        width: 400
        height: 400
        radius: height / 23
        anchors.right: parent.right
        anchors.rightMargin: 80
        anchors.top: parent.top
        anchors.topMargin: 80
    }

    Rectangle {
        id: rectBg2
        color: "#64c3defa"
        width: 400
        height: 400 - (anchors.topMargin - rectBg1.anchors.topMargin) + 40
        radius: height / 23
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 210
    }

    ComTextEditBold {
        id: lblTxt1
        text: "光通讯"
        font.pixelSize: 30
        color: "#000000"
        anchors.left: rectBg2.left
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 150 + (lblTxt2.font.pixelSize - font.pixelSize)
    }

    ComTextEditBold {
        id: lblTxt2
        text: "网关"
        color: "#000000"
        font.pixelSize: 50
        anchors.top: parent.top
        anchors.left: lblTxt1.right
        anchors.topMargin: 150
    }

    ComTextEditBold {
        id: lblTxt3
        text: "适配器"
        color: "#000000"
        font.pixelSize: 30
        anchors.top: parent.top
        anchors.left: lblTxt2.right
        anchors.topMargin: 150 + (lblTxt2.font.pixelSize - font.pixelSize)
    }

    ComTextEdit {
        id: lblTxt4
        text: "Ver " + Consts.versionStr
        font.pixelSize: 12
        anchors.top: parent.top
        anchors.left: lblTxt3.right
        anchors.leftMargin: 10
        anchors.topMargin: 150 + (lblTxt2.font.pixelSize - font.pixelSize)
    }

    ComTextEdit {
        id: lblTxt5
        text: "by: HyEISN"
        font.pixelSize: 18
        anchors.top: lblTxt1.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
    }

    ComTextEdit {
        id: lblTxt6
        text: "Tel: 18929252393"
        font.pixelSize: 18
        anchors.top: lblTxt5.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
    }

    ComLabel {
        id: lblTxt7
        anchors.top: lblTxt6.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
        font.pixelSize: 18
        text: `@M: <a href="hyeisn@hotmail.com">hyeisn@hotmail.com</a>`

        ComToolTip {
            id: emailTip
            text: "mail to me"
            delay: 50
            y: (height / 2) + 8
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: emailTip.visible = true
            onExited: emailTip.visible = false
            onClicked: Qt.openUrlExternally("mailto:?to=罗骏<hyeisn@hotmail.com>&subject=您好, 请在此处写入标题!&body=您好, 请在此处键入咨询内容.")
        }
    }

    ComTextEdit {
        id: lblTxt8
        text: "WebSite: "
        font.pixelSize: 18
        anchors.top: lblTxt7.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
    }

    Label {
        id: lblWebSite
        // text: `<a href="www.example.com">www.example.com</a>`
        text: "Comming soon..."
        font.pixelSize: 18
        anchors.top: lblTxt8.top
        anchors.left: lblTxt8.right

        // ComToolTip {
        //     id: webSiteTip
        //     text: "点击访问个人网站"
        //     delay: 50
        //     y: (height / 2) + 8
        // }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            // onEntered: webSiteTip.visible = true
            // onExited: webSiteTip.visible = false
            // onClicked: Qt.openUrlExternally("http://www.example.com")
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
