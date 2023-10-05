import QtQuick
import QtQuick.Window
import QtQuick.Controls
import AppQmlBackend
import DeviceBackend

Item {
    id: page

    Pane {
        id: mainPane
        anchors.fill: parent
        anchors.topMargin: -24
        leftPadding: 0
        rightPadding: 0
        bottomPadding: 0
        background: Rectangle {
            color: "White"
        }

        Pane {
            id: headPane
            background: Rectangle {
                color: "White"
            }

            TabBar {
                id: tabBar
                background: Rectangle {
                    color: "White"
                }

                TabButton {
                    text: qsTr("Home")
                    width: 85
                    icon.source: "resources/icon-home.svg"
                    icon.height: Consts.icon_h
                    icon.width: Consts.icon_w
                    onClicked: {
                        if (stackView.currentItem == homePage)
                            return
                        stackView.replace(null, homePage)
                    }
                }
                TabButton {
                    text: qsTr("设备监控")
                    width: 110
                    icon.source: "resources/icon-camera.svg"
                    icon.height: Consts.icon_h
                    icon.width: Consts.icon_w
                    onClicked: {
                        if (stackView.currentItem == watchingPage)
                            return
                        stackView.replace(null, watchingPage)
                    }
                }
                TabButton {
                    text: qsTr("TLogs")
                    width: 100
                    icon.source: "resources/icon-document.svg"
                    icon.height: Consts.icon_h
                    icon.width: Consts.icon_w
                    onClicked: {
                        if (stackView.currentItem == tlogsPage)
                            return
                        stackView.replace(null, tlogsPage)
                    }
                }
                TabButton {
                    text: qsTr("Sets")
                    width: 83
                    icon.source: "resources/icon-settings.svg"
                    icon.height: Consts.icon_h
                    icon.width: Consts.icon_w
                    onClicked: {
                        if (stackView.currentItem == setsPage)
                            return
                        stackView.replace(null, setsPage)
                    }
                }
                TabButton {
                    id: btnTabTests
                    text: qsTr("TESTS")
                    width: 90
                    icon.source: "resources/icon-flask.svg"
                    icon.height: Consts.icon_h
                    icon.width: Consts.icon_w
                    visible: Consts.debug
                    enabled: Consts.debug
                    onClicked: {
                        if (stackView.currentItem == testPage)
                            return
                        stackView.replace(null, testPage)
                    }
                }
            }
        }

        Pane {
            id: contentPane
            anchors.top: headPane.bottom
            anchors.topMargin: -10
            anchors.bottom: parent.bottom
            width: parent.width
            background: Rectangle {
                color: "White"
            }

            StackView {
                id: stackView
                anchors.fill: parent

                PageHome {
                    id: homePage
                    view: stackView
                }
                PageWatching {
                    id: watchingPage
                    view: stackView
                    log: tlogsPage
                    deviceCenter: deviceCenter
                }
                PageTLogs {
                    id: tlogsPage
                    view: stackView
                    bgservice: bgservice
                }
                PageSets {
                    id: setsPage
                    view: stackView
                    bgservice: bgservice
                    deviceCenter: deviceCenter
                }
                T_PageTests {
                    id: testPage
                    view: stackView
                }
            }
        }
    }

    ProgmService {
        id: progservice
    }

    QmlService {
        id: bgservice
    }

    DeviceCenter {
        id: deviceCenter
        onDeviceConnected: (dId) => {
            GlobalVariable[`device${dId}Connected`] = true
            tlogsPage.appendSuccessLog(dId, "已建立连接.")
        }
        onDeviceDisconnect: (dId) => {
            GlobalVariable[`device${dId}Connected`] = false
            tlogsPage.appendErrorLog(dId, "已断开连接.")
        }
        onDeviceConnectFailed: (dId) => {
            tlogsPage.appendErrorLog(dId, "连接失败或连接已断开.")
        }
        onDeviceApplied: (dId, ip, port) => {
            tlogsPage.appendNormalLog(dId, `已采用了新的连接参数 ${ip}:${port} , 正在重新连接.`)
        }
        onBarcodeReceived: (dId, barcode) => {
            tlogsPage.appendNormalLog(dId, `接收到条码内容 => ${barcode}`)
            GlobalVariable.deviceMap[dId].rx()
        }
        onBarcodeQueryFailed: (dId, barcode, result) => {
            tlogsPage.appendErrorLog(dId, `查询条码信息 ${barcode} 失败, 返回结果 => ${JSON.stringify(result)}`)
        }
        onBarcodeQuerySuccess: (dId, barcode, result) => {
            tlogsPage.appendNormalLog(dId, `查询条码信息 ${barcode} 成功, 返回结果 => ${JSON.stringify(result)}`)
        }
        onPlcTx: (dId) => {
            GlobalVariable.deviceMap[dId].tx()
        }
        onPlcRx: (dId) => {
            GlobalVariable.deviceMap[dId].rx()
        }
    }

    function showDialog(title, content, type, acceptCb, rejectCb) {
        let com = Qt.createComponent("com/ComDialog.qml");
        let dialog = com.createObject(page, { title, content, type, acceptCb, rejectCb });
        dialog.open();
    }

    Component.onCompleted: {
        // debug options
        if (!Consts.debug) {
            testPage.destroy()
        }
        stackView.replace(setsPage, null)
        stackView.replace(tlogsPage, null)
        stackView.replace(watchingPage, null)
        stackView.replace(homePage, null)
    }
}
