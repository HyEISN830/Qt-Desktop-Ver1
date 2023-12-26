import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import Qt.labs.qmlmodels
import AppQml
import AppQmlBackend

import "js/Common.js" as JSLib

Item {
    property StackView view
    property QmlService bgservice
    property bool loading: false

    id: page
    opacity: 0

    ComDelay {
        id: delay
    }

    ComLoading {
        visible: parent.loading
    }

    ComPane {
        anchors.fill: parent
        padding: 0

        Rectangle {
            id: operateArea
            height: 40
            anchors.left: parent.left
            anchors.right: parent.right
            color: "transparent"

            Row {
                anchors.fill: parent
                layoutDirection: Qt.RightToLeft
                spacing: 8

                ComButton {
                    text: "导出日志"
                    onClicked: bgservice.saveContent2Log(`${JSLib.now()}.txt`, textEdit.getText(0, textEdit.length)) && JSLib.showDialog(this, "提示", "文件已保存到程序下的 log 文件夹中, \n请查看!", "Info")
                }

                ComButton {
                    text: "清空日志"
                    onClicked: textEdit.clear()
                }

                FileDialog {
                    id: saveLogFile
                    nameFilters: ["文本文件 (*.txt)"]
                    onAccepted: console.log(saveLogFile.selectedFile)
                }
            }
        }

        ScrollView {
            anchors.top: operateArea.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            background: Rectangle {
                color: "#2f3542"
                radius: 5
            }

            ComTextEdit {
                id: textEdit
                padding: 5
                anchors.fill: parent
                textFormat: Text.RichText
                readOnly: true
            }
        }
    }

    function _clearIfMax() {
        let set = bgservice.takeSetting("logLength")
        if (textEdit.length > (set ? parseInt(set) : 10000))
            textEdit.clear()
    }

    function appendNormalLog(dId, msg) {
        _clearIfMax()
        let str = `<b><font font-size=15 color="#3498db">[${JSLib.now()}] - ${dId ? "\"" + GlobalVariable.deviceMap[dId].content + "\"" : ""}: ${msg}</font></b>`
        let start = textEdit.length
        textEdit.append(str)
        bgservice.addAppLog(textEdit.getText(start, textEdit.length), 3)
    }

    function appendSuccessLog(dId, msg) {
        _clearIfMax()
        let str = `<b><font font-size=15 color="#2ecc71">[${JSLib.now()}] - ${dId ? "\"" + GlobalVariable.deviceMap[dId].content + "\"" : ""}: ${msg}</font></b>`
        let start = textEdit.length
        textEdit.append(str)
        bgservice.addAppLog(textEdit.getText(start, textEdit.length), 1)
    }

    function appendErrorLog(dId, msg) {
        _clearIfMax()
        let str = `<b><font font-size=15 color="#e74c3c">[${JSLib.now()}] - ${dId ? "\"" + GlobalVariable.deviceMap[dId].content + "\"" : ""}: ${msg}</font></b>`
        let start = textEdit.length
        textEdit.append(str)
        bgservice.addAppLog(textEdit.getText(start, textEdit.length), 2)
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }

    Component.onCompleted: {
        GlobalVariable.txtLog = textEdit
    }
}
