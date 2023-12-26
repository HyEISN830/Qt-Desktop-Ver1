import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend
import DeviceBackend

import "./js/Common.js" as JSLib

Item {
    property StackView view
    property int panewide: r.width / 6.15
    property int paneradius: 8

    id: page

    Row {
        id: r
        anchors.fill: parent
        spacing: 8

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            radius: paneradius
            color: "#ecf0f1"

            Column {
                id: w1Header
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: 8

                ComTextEditBold {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "W1"
                    font.pixelSize: 40
                    readOnly: true
                }

                ComTextEdit {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "当前扫到条码:"
                    font.pixelSize: 17
                    readOnly: true
                }

                ComTextField {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width - 16
                    text: "无条码"
                }

                ComTextEdit {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "当前执行工单:"
                    font.pixelSize: 17
                    readOnly: true
                }

                ComTextField {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width - 16
                    text: "无工单"
                }

                ComTextEdit {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "当前条码列表:"
                    font.pixelSize: 17
                    readOnly: true
                }
            }

            ScrollView {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: w1Header.bottom
                anchors.topMargin: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 8
                width: parent.width - 16
                background: Rectangle {
                    color: "#30fd79a8"
                    radius: 8
                }

                Column {
                    x: 8
                    y: 8
                    spacing: 6

                    Repeater {
                        model: 20

                        Rectangle {
                            color: "transparent"
                            width: barcode.width + btndelbarcode.width + row.spacing
                            height: 30

                            Row {
                                id: row
                                anchors.fill: parent
                                spacing: 8

                                ComTextEdit {
                                    id: barcode
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: "15B2NNPA00ZPA2500041"
                                    readOnly: true
                                }

                                RoundButton {
                                    id: btndelbarcode
                                    height: 30
                                    width: 30
                                    icon.color: "red"
                                    icon.source: "resources/icon-close.svg"

                                    ComToolTip {
                                        visible: parent.hovered
                                        text: "删除该条码"
                                        delay: 400
                                        y: -40
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            radius: paneradius
            color: "#ecf0f1"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            radius: paneradius
            color: "#ecf0f1"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            radius: paneradius
            color: "#ecf0f1"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            radius: paneradius
            color: "#ecf0f1"
        }

        Rectangle {
            width: panewide
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            radius: paneradius
            color: "#ecf0f1"
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
