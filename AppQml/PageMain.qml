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
                    text: qsTr("码垛状态")
                    width: 110
                    icon.source: "resources/icon-boxes.svg"
                    icon.height: Consts.icon_h
                    icon.width: Consts.icon_w
                    onClicked: {
                        if (stackView.currentItem == lineStatePage)
                            return
                        stackView.replace(null, lineStatePage)
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
                PageLineState {
                    id: lineStatePage
                    view: stackView
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
            tlogsPage.appendNormalLog(dId, `已采用了新的连接参数 <font color="#f1c40f">${ip}:${port}</font> , 正在重新连接.`)
        }
        onBarcodeReceived: (dId, barcode) => {
            if (barcode.indexOf("OK,KEYENCE") !== 0)
                tlogsPage.appendNormalLog(dId, `接收到条码内容 => <font color="${(barcode + '') == 'NG' ? '#e74c3c' : '#f1c40f'}">${barcode}</font>`)
            GlobalVariable.deviceMap[dId].rx()
        }
        onBarcodeQueryFailed: (dId, barcode, result) => {
            tlogsPage.appendErrorLog(dId, `响应条码/接口信息 <font color="#f1c40f">${barcode}</font> 失败, 返回结果 => <font color="#f1c40f">${JSON.stringify(result)}</font>`)
        }
        onBarcodeQuerySuccess: (dId, barcode, result) => {
            let resultstr = JSON.stringify(result)
            let logcontent = `响应条码接口/条码信息 <font color="#f1c40f">${barcode}</font> 成功, 返回结果 => <font color="#f1c40f">${resultstr}</font>`

            if (resultstr.indexOf("已入库") > -1 || resultstr.indexOf("未下线") > -1)
                tlogsPage.appendErrorLog(dId, logcontent)
            else
                tlogsPage.appendNormalLog(dId, logcontent)
        }
        onBarcodeGotoNormal: (dId, barcode) => {
            tlogsPage.appendNormalLog(dId, `条码 <font color="#f1c40f">${barcode}</font> 产品将流向 <font color="#2ecc71">-正常-</font> 线.`)
        }
        onBarcodeGotoError: (dId, barcode) => {
            tlogsPage.appendErrorLog(dId, `条码 <font color="${(barcode + '') == 'NG' ? '#e74c3c' : '#f1c40f'}">${barcode}</font> 产品将流向 <font color="#e74c3c">-异常-</font> 线.`)
        }
        onBarcodeGotoChange: (dId, line, orderNo, len, wide, height) => {
            tlogsPage.appendNormalLog(dId, `已换产为 => <font color="#f1c40f">${orderNo}</font> 产品.`)
        }
        onBarcodeNoAvailableStack: (dId) => {
            tlogsPage.appendErrorLog(dId, `发起了机械臂已码垛物料完成请求, 但是未找到当前线体已扫码的物料.`)
        }
        onBarcodePullUped: (dId, barcode) => {
            tlogsPage.appendNormalLog(dId, `条码 <font color="#f1c40f">${barcode}</font> 产品已被机械臂码好且已加入到码垛中.`)
        }
        onBarcodeUploaded: (dId, barcode) => {
            tlogsPage.appendNormalLog(dId, `条码 <font color="#f1c40f">${barcode}</font> 产品已扫码确认.`)
        }
        onBarcodeApproveOut: (dId) => {
            tlogsPage.appendNormalLog(dId, `WMS 准许出料.`)
        }
        onBarcodeRejectOut: (dId) => {
            tlogsPage.appendErrorLog(dId, `WMS 拒绝出料.`)
        }
        onBarcodeSendedKeep: (dId, cmd) => {
            GlobalVariable.deviceMap[dId].tx()
        }
        onBarcodeChangeReady: (dId) => {
            tlogsPage.appendNormalLog(dId, `即将换产.`)
        }
        onPlcTx: (dId) => {
            GlobalVariable.deviceMap[dId].tx()
        }
        onPlcRx: (dId) => {
            GlobalVariable.deviceMap[dId].rx()
        }
        onPlcWrited: (dId, addr, value) => {
            tlogsPage.appendNormalLog(dId, `PLC寄存器 <font color="#f1c40f">${addr}</font> 写入 => <font color="#f1c40f">${value}</font>`)
        }
        onPlcPullUp: (dId, line) => {
            tlogsPage.appendNormalLog(dId, `<font color="#f1c40f">${resolveLine(line)}</font> 线机械臂已码好一个物料.`)
        }
        onPlcDuplicateClamped: (dId, line, diff) => {
            tlogsPage.appendErrorLog(dId, `由于PLC在${resolveLine(line)}线上, 一定秒数内重复发起夹料完成, 本次夹料完成已忽略. 相隔 +${diff}s`)
        }
        onRobotSended: (dId, content) => {
            tlogsPage.appendNormalLog(dId, `发送到机械臂内容 => <font color="#f1c40f">${content}</font>`)
        }
        onRobotReceived: (dId, content) => {
            tlogsPage.appendNormalLog(dId, `接收到机械臂内容 => <font color="#f1c40f">${content}</font>`)
        }
        onRobotHeartStopped: (dId) => {
            tlogsPage.appendErrorLog(dId, "由于机械臂长时间未传送心跳数据, 判定为已死亡, 即将重连.")
        }
        onRobotTx: (dId) => {
            GlobalVariable.deviceMap[dId].tx()
        }
        onRobotRx: (dId) => {
            GlobalVariable.deviceMap[dId].rx()
        }
        onSchedulingTx: (dId) => {
            GlobalVariable.deviceMap[dId].tx()
        }
        onSchedulingRx: (dId) => {
            GlobalVariable.deviceMap[dId].rx()
        }
    }

    function showDialog(title, content, type, acceptCb, rejectCb) {
        let com = Qt.createComponent("com/ComDialog.qml");
        let dialog = com.createObject(page, { title, content, type, acceptCb, rejectCb });
        dialog.open();
    }

    function resolveLine(line) {
        switch (line) {
        case 2:
            return "W1"
        case 3:
            return "W2"
        case 4:
            return "W3"
        case 5:
            return "N3"
        case 6:
            return "N2"
        case 7:
            return "N1"
        }
    }

    Component.onCompleted: {
        // debug options
        if (!Consts.debug) {
            testPage.destroy()
        }
        stackView.replace(setsPage, null)
        stackView.replace(tlogsPage, null)
        stackView.replace(lineStatePage, null)
        stackView.replace(watchingPage, null)
        stackView.replace(homePage, null)
    }
}
