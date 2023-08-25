import QtQuick
import QtQuick.Controls
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
        source: "resources/logo.png"
        width: 70
        height: 70
        anchors.left: rectBg1.left
        anchors.leftMargin: 10
        anchors.top: rectBg1.top
        anchors.topMargin: 10
        mipmap: true
        z: 1
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
        text: "暖通"
        font.pixelSize: 30
        color: "#000000"
        anchors.right: lblTxt2.left
        anchors.top: parent.top
        anchors.topMargin: 150 + (lblTxt2.font.pixelSize - font.pixelSize)
    }

    ComTextEditBold {
        id: lblTxt2
        text: "控制"
        color: "#000000"
        font.pixelSize: 50
        anchors.top: parent.top
        anchors.right: lblTxt3.left
        anchors.topMargin: 150
    }

    ComTextEditBold {
        id: lblTxt3
        text: "系统"
        color: "#000000"
        font.pixelSize: 30
        anchors.top: parent.top
        anchors.right: lblTxt4.left
        anchors.rightMargin: 10
        anchors.topMargin: 150 + (lblTxt2.font.pixelSize - font.pixelSize)
    }

    ComTextEdit {
        id: lblTxt4
        text: "Ver " + Consts.versionStr
        font.pixelSize: 12
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: 140
        anchors.topMargin: 150 + (lblTxt2.font.pixelSize - font.pixelSize)
    }

    ComTextEdit {
        id: lblTxt5
        text: "by: 中山市铭辉智能装备有限公司."
        font.pixelSize: 18
        anchors.top: lblTxt1.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
    }

    ComTextEdit {
        id: lblTxt6
        text: "Tel: 0760-22265892."
        font.pixelSize: 18
        anchors.top: lblTxt5.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
    }

    ComTextEdit {
        id: lblTxt7
        text: "Addr.: 中山市东凤镇东凤大道南268号."
        font.pixelSize: 18
        anchors.top: lblTxt6.bottom
        anchors.topMargin: 10
        anchors.left: lblTxt1.left
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
        text: `<a href="www.zsmhzb.com">www.zsmhzb.com</a>`
        font.pixelSize: 18
        anchors.top: lblTxt8.top
        anchors.left: lblTxt8.right

        ComToolTip {
            id: webSiteTip
            text: "点击访问铭辉网站"
            delay: 50
            y: (height / 2) + 8
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: webSiteTip.visible = true
            onExited: webSiteTip.visible = false
            onClicked: Qt.openUrlExternally("http://www.zsmhzb.com")
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
