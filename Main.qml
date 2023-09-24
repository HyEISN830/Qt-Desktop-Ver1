import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt.labs.folderlistmodel
import AppQml
import QmlFontLoader
import AC_OU_CMS

ApplicationWindow {
    property bool needclose: false
    property PageMain pagemain: null

    id: appWindow
    height: Consts.globalresolution_h
    width: Consts.globalresolution_w
//    minimumHeight: 900
//    minimumWidth: 1200
    minimumHeight: Consts.globalresolution_h
    minimumWidth: Consts.globalresolution_w
    visible: true
    title: qsTr("MFS")
    background: Rectangle {
        color: "White"
    }
    menuBar: MenuBar {
        background: Rectangle {
            color: "#95afc0"
        }
        Menu {
            title: qsTr("&File")
            Action { text: qsTr("&New...") }
            MenuSeparator { }
            Action {
                text: qsTr("&Quit")
                onTriggered: {
                    Qt.quit()
                }
            }
        }
        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                onTriggered: {
                    helpWindow.open()
                }
            }
        }
    }
    font.family: Consts.fontNormal
    onClosing: (e) => {
        if (!needclose) {
            e.accepted = false
            dialog.open()
            return
        }
    }

    DirectoryFontLoader {
        id: fontLoader
        done: function () {
//            let com = Qt.createComponent("./AppQml/PageMain.qml");
//            let dialog = com.createObject(appWindow);
//            pagemain = dialog
        }
    }

    ComHelpDialog {
        id: helpWindow
    }

    PageMain {
        id: mainPage
        anchors.fill: parent
    }

    Dialog {
        id: dialog
        title: "是否退出程序?"
        standardButtons: Dialog.Ok | Dialog.Cancel
        anchors.centerIn: parent

        onAccepted: {
            needclose = true
            Qt.quit()
        }
    }

    Component.onDestruction: {
        if (pagemain) pagemain.destroy()
    }
}
