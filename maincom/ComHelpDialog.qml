import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend

Dialog {
    id: helpWindow
    width: 600
    height: 400
    anchors.centerIn: Overlay.overlay
    standardButtons: Dialog.Ok
    closePolicy: Dialog.NoAutoClose
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
                source: "../resources/icon-help-globle.svg"
            }

            TextEdit {
                anchors.left: dialogImage.right
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 1
                text: qsTr("About")
                font.bold: true
                font.pixelSize: 20
                font.family: "JetBrains Mono"
                verticalAlignment: Text.AlignVCenter
                selectByMouse: true
                readOnly: true
                selectByKeyboard: false
                mouseSelectionMode: TextInput.SelectCharacters
            }
        }
    }

    QmlService {
        id: bgservice
    }

    Pane {
        id: contentPane
        width: parent.width
        y: dialogPane.height + 6
        background: Rectangle {
            color: "transparent"
        }

        TextEdit {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            text: "Comming soon"
            font.pixelSize: 13
            font.family: "JetBrains Mono"
            verticalAlignment: Text.AlignVCenter
            selectByMouse: true
            readOnly: true
            selectByKeyboard: false
            mouseSelectionMode: TextInput.SelectCharacters

            Button {
                anchors.top: parent.bottom
                anchors.topMargin: 8
                anchors.left: parent.left
                text: "联系我们"
                height: Consts.button_h

                Connections {
                    function onClicked() {
                        bgservice.openurlwithbrowser("http://103.73.119.198:4001/index.html");
                    }
                }
            }
        }
    }
}
