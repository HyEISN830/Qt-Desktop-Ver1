import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels
import AppQml
import AppQmlBackend

import "js/Common.js" as Common

Item {
    property StackView view
    property ParasDbApi db
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
        id: rootPane
        topPadding: -10
        leftPadding: 0
        anchors.fill: parent

        Column {
            spacing: 5

            ComPane {
                id: headerPane
                height: 120

                Column {
                    Row {
                        id: fieldsrow
                        spacing: 6

                        ComTextField {
                            id: txtstarttime
                            text: Common.now()
                            placeholderText: "开始时间"
                            width: 180
                            enabled: !chkdistimequery.checked
                        }

                        ComTextEdit {
                            // 占位&间隔 元素
                            text: "-"
                            width: 15
                            height: parent.height
                            horizontalAlignment: Text.AlignHCenter
                        }

                        ComTextField {
                            id: txtendtime
                            text: Common.now()
                            width: 180
                            placeholderText: "结束时间"
                            enabled: !chkdistimequery.checked
                        }

                        ComLabel {
                            leftPadding: 10
                            text: "Ip:"
                            anchors.verticalCenter: txtip.verticalCenter
                        }

                        ComTextField {
                            id: txtip
                            height: parent.height
                            width: 120
                            placeholderText: "IP"
                        }

                        ComLabel {
                            leftPadding: 10
                            text: "条码:"
                            anchors.verticalCenter: txtbarcode.verticalCenter
                        }

                        ComTextField {
                            id: txtbarcode
                            height: parent.height
                            width: 120
                            placeholderText: "条码"
                        }

                        ComLabel {
                            leftPadding: 10
                            text: "检测结果:"
                            anchors.verticalCenter: cmbtestresult.verticalCenter
                        }

                        ComboBox {
                            id: cmbtestresult
                            height: txtbarcode.height
                            textRole: "text"
                            valueRole: "value"
                            model: [
                                { value: "", text: "无" },
                                { value: "0", text: "NG" },
                                { value: "1", text: "OK" },
                            ]
                            padding: 0
                            width: 120
                        }
                    }

                    Row {
                        height: 35

                        CheckBox {
                            id: chkdistimequery
                            height: parent.height
                            text: "禁用时间查询"
                            checked: true
                        }
                    }

                    Row {
                        width: fieldsrow.width
                        layoutDirection: Qt.RightToLeft

                        ComButton {
                            id: btnquery
                            text: "查询"

                            onClicked: {
                                if (verifyfields()) queryDatas()
                            }
                        }

                        RoundButton {
                            width: btnquery.height
                            height: width
                            icon.source: "resources/icon-reload.svg"
                            onClicked: {
                                showDialog("确定", "**此操作会将所有字段恢复为默认值", "Warn", resetFields)
                            }
                        }
                    }
                }
            }

            ComTable {
                id: table
                width: rootPane.width
                height: 650
                copycb: (content) => bgservice.copy2clipboard(content)
                columns: [
                    {
                      "name": "#",
                      "width": 50,
                      "alias": "#"
                    },
                    {
                      "name": "IP",
                      "width": 150,
                      "alias": "ip"
                    },
                    {
                      "name": "测试时间",
                      "width": 180,
                      "alias": "testtime"
                    },
                    {
                      "name": "条码",
                      "width": 200,
                      "alias": "barcode"
                    },
                    {
                      "name": "制热温差",
                      "alias": "hotdiff"
                    },
                    {
                      "name": "制热电流",
                      "alias": "hoteleca"
                    },
                    {
                      "name": "制热功率",
                      "alias": "hotelecw"
                    },
                    {
                      "name": "制热压力",
                      "alias": "hotmpa"
                    },
                    {
                      "name": "制冷温差",
                      "alias": "colddiff"
                    },
                    {
                      "name": "制冷电流",
                      "alias": "coldeleca"
                    },
                    {
                      "name": "制冷功率",
                      "alias": "coldelecw"
                    },
                    {
                      "name": "制冷压力",
                      "alias": "coldmpa"
                    },
                    {
                      "name": "工作电压",
                      "alias": "workeleca"
                    },
                    {
                      "name": "测试结果",
                      "alias": "testresult"
                    }
                ]
                pageChangedCb: function (curPage, pageSize) {
                    queryDatas()
                }
            }
        }
    }

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }

    function verifyfields() {
        if (!chkdistimequery.checked && (Common.dateValid(txtstarttime.text) || Common.dateValid(txtendtime.text))) {
            showDialog("错误", `  请修正开始 或 结束的时间格式, 如:\n${Common.now()}`, "Erro")
            return false
        }

        return true
    }

    function queryDatas() {
        loading = true
        delay.delay(100, () => {
            try {
                let rowctns = db.getTlogsCtn(chkdistimequery.checked ? "" : txtstarttime.text
                                             , chkdistimequery.checked ? "" : txtendtime.text
                                             , txtip.text
                                             , txtbarcode.text
                                             , cmbtestresult.currentValue)
                let tlogs = db.getTlogs(table.curPage
                                        , table.pageSize
                                        , chkdistimequery.checked ? "" : txtstarttime.text
                                        , chkdistimequery.checked ? "" : txtendtime.text
                                        , txtip.text
                                        , txtbarcode.text
                                        , cmbtestresult.currentValue)
                let kvmirror = {}

                table.rowCount = rowctns

                for (let item in cmbtestresult.model)
                    kvmirror[cmbtestresult.model[item].value] = cmbtestresult.model[item].text

                for (let i in tlogs) {
                    tlogs[i].testtime = tlogs[i].testtime.replace("T", " ").replace(".000", "")
                    tlogs[i].testresult = kvmirror[tlogs[i].testresult]
                }

                table.overwrite(tlogs)
            }
            finally {
                loading = false
            }
        })
    }

    function resetFields() {
        txtstarttime.text = Common.now()
        txtendtime.text = Common.now()
    }

    function showDialog(title, content, type, acceptCb, rejectCb) {
        let com = Qt.createComponent("com/ComDialog.qml");
        let dialog = com.createObject(page, { title, content, type, acceptCb, rejectCb });
        dialog.open();
    }

    Component.onCompleted: {
    }
}
