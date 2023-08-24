import QtQuick
import QtQuick.Controls

Dialog {
    /*
      Support as:
        Info = infomation
        Qust = question
        Erro = error
        Warn = warning
      "Info" is default
    */
    property string type: "Info"
    property string content: ""
    property var acceptCb: null
    property var rejectCb: null

    id: cmoponent
    visible: false
    modal: true
    focus: true
    anchors.centerIn: Overlay.overlay
    standardButtons: Dialog.Ok | Dialog.Cancel
    closePolicy: Dialog.NoAutoClose
    width: 300
    height: 200
    header: Item {
        Pane {
            id: dialogPane
            width: parent.width
            height: 32
            anchors.top: parent.top
            anchors.topMargin: 10
            background: Rectangle {
                color: "transparent"
            }

            Image {
                id: dialogImage
                width: 32
                height: 32
                anchors.left: parent.left
                anchors.leftMargin: 20
                mipmap: true
            }

            ComTextEdit {
                anchors.left: dialogImage.right
                anchors.leftMargin: 10
                anchors.top: dialogImage.top
                anchors.topMargin: 3
                text: title
                font.bold: true
                font.pixelSize: 20
            }
        }
    }

    Pane {
        id: contentPane
        width: parent.width
        y: dialogPane.height + 6
        background: Rectangle {
            color: "transparent"
        }

        ComTextEdit {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: content
            font.pixelSize: 13
        }
    }

    Connections {
        target: cmoponent
        function onAccepted() {
            if (acceptCb) acceptCb();
        }
        function onRejected() {
            if (rejectCb) rejectCb();
        }
        function onClose() {
            cmoponent.destroy();
        }
    }

    Component.onCompleted: {
        switch (type) {
            case "Info":
                dialogImage.source = "../resources/icon-info.svg"
                standardButtons = Dialog.Ok;
                break;
            case "Warn":
                dialogImage.source = "../resources/icon-warn.svg"
                standardButtons = Dialog.Ok | Dialog.Cancel;
                break;
            case "Erro":
                dialogImage.source = "../resources/icon-erro.svg"
                standardButtons = Dialog.Ok;
                break;
            case "Qust":
                dialogImage.source = "../resources/icon-qust.svg"
                standardButtons = Dialog.Ok | Dialog.Cancel;
                break;
        }
    }
}
