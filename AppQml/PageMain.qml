import QtQuick
import QtQuick.Window
import QtQuick.Controls
import AppQmlBackend

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
                    icon.source: "resources/icon-stats.svg"
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
        if (!initDb()) return false;
        stackView.replace(setsPage, null)
        stackView.replace(tlogsPage, null)
        stackView.replace(watchingPage, null)
        stackView.replace(homePage, null)
    }
}
