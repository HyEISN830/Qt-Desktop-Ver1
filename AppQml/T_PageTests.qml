import QtQuick
import QtQuick.Controls
import AppQml

Item {
    property StackView view

    id: page
    opacity: 0

    QmlCppDemo {
        id: qmlCppDemo

        Connections {
            target: qmlCppDemo
            function onMdclientChanged (state) {
                console.log("Modbus Connection state changed to:", state)
                switch (state) {
                    case 0:
                    case 1:
                        modbusStatusBar.color = "#e74c3c";
                        break;
                    case 2:
                        modbusStatusBar.color = "#2ecc71";
                        break;
                    case 3:
                        modbusStatusBar.color = "#e74c3c";
                        break;
                }
            }
        }
    }

    GroupBox {
        id: grpModbus
        width: 300
        height: 220
        title: qsTr("Modbus")

        Rectangle {
            id: modbusStatusBar
            width: 150
            height: 8
            radius: 4
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#e74c3c"
        }

        TextField {
            id: txtModbusHost
            height: 35
            width: 200
            anchors.top: modbusStatusBar.bottom
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.right: parent.right
            placeholderText: "Device Host"
            text: "127.0.0.1"
        }

        TextField {
            id: txtModbusPort
            height: 35
            width: 200
            anchors.left: txtModbusHost.left
            anchors.right: txtModbusHost.right
            anchors.top: txtModbusHost.bottom
            anchors.topMargin: 10
            placeholderText: "Device Port"
            text: "502"
        }

        Label {
            id: modbusLabel
            text: qsTr("state")
            anchors.top: txtModbusPort.bottom
            anchors.right: txtModbusPort.right
            color: "#2779F6"

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    let mdclientstate = qmlCppDemo.mdclientstate();
                    let statstr = "Unconnected";

                    switch (mdclientstate) {
                        case 0:
                            statstr = "Unconnected";
                            break;
                        case 1:
                            statstr = "Connecting";
                            break;
                        case 2:
                            statstr = "Connected";
                            break;
                        case 3:
                            statstr = "Closing";
                            break;
                    }

                    showDialog("State", mdclientstate + "\n" + mdclientstate + " is " + statstr, "Info")
                }
            }
        }

        Button {
            id: btnModbusconn
            height: Consts.button_h
            anchors.left: txtModbusHost.left
            anchors.top: btnModbusSend.top
            text: qsTr("Connect")

            Connections {
                target: btnModbusconn
                function onClicked() {
                    if (!grpFieldVerify()) {
                        showDialog("错误", "请补全所有字段!", "Erro");
                        return false
                    }

                    if (qmlCppDemo.mdclientstate() == 2) {
                        showDialog("警告", "Modbus已连接, 请勿重复操作!", "Warn")
                        return false
                    }

                    showDialog("开始连接", "连接状态Ok: " + qmlCppDemo.openmdclient(txtModbusHost.text, txtModbusPort.text), "Info");
                }
            }
        }

        Button {
            id: btnModbusSend
            height: Consts.button_h
            anchors.bottom: parent.bottom
            anchors.right: txtModbusHost.right
            text: qsTr("Send")

            Connections {
                target: btnModbusSend
                function onClicked() {
                    if (!grpFieldVerify()) {
                        showDialog("错误", "请补全所有字段!", "Erro");
                        return false
                    }

//                    console.log(qmlCppDemo.trysendmodbus(txtModbusHost.text, txtModbusPort.text));
                    qmlCppDemo.mdclientsend();
                }
            }
        }
    }

    GroupBox {
        id: grpDatabase
        anchors.left: grpModbus.right
        anchors.leftMargin: 10
        anchors.top: grpModbus.top
        width: 300
        height: 220
        title: qsTr("Database")

        TextField {
            id: txtDatabaseHost
            height: 35
            width: 200
            anchors.top: parent.top
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.right: parent.right
            placeholderText: "Database Host"
            text: "hyeisn.cn"
        }

        TextField {
            id: txtDatabasePort
            height: 35
            width: 200
            anchors.top: txtDatabaseHost.bottom
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.right: parent.right
            placeholderText: "Database Port"
            text: "5432"
        }

        Button {
            height: Consts.button_h
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            text: qsTr("Connect")

            Connections {
                function onClicked() {
                    let ok = qmlCppDemo.openpostgresql(txtDatabaseHost.text, txtDatabasePort.text)
                    showDialog("DbOpen", ok ? "Success" : "Failed", ok ? "Info" : "Erro")
                }
            }
        }

        Button {
            height: Consts.button_h
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            text: qsTr("Query")

            Connections {
                function onClicked() {
                    let results = qmlCppDemo.querypostgresql()

                    for (let key in results) {
                        console.log(results[key])
                    }
                }
            }
        }
    }

    Label {
        text: qsTr("Testing page")
        anchors.centerIn: parent
    }

    OpacityAnimator {
        target: testPage;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == target
    }

    function grpFieldVerify() {
        return !((txtModbusHost.text.length == 0 || txtModbusHost.text.trim().length == 0) ||
                (txtModbusPort.text.length == 0 || txtModbusPort.text.trim().length == 0));
    }

    function showDialog(title, content, type) {
        let com = Qt.createComponent("com/ComDialog.qml");
        let dialog = com.createObject(page, { title, content, type });
        dialog.open();
    }
}
