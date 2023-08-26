import QtQuick
import QtQuick.Controls
import AppQml
import AppQmlBackend

Item {
    property StackView view
    property QmlService bgservice: null

    id: page
    opacity: 0

    ScrollView {
        anchors.fill: parent
        padding: 0

        Column {
            spacing: 5

            Rectangle {
                Column {
                    ComExpand {
                        width: 200
                        body: Component {
                            Rectangle {
                                height: 50
                                color: "blue"
                            }
                        }
                    }

                    ComExpand {
                        width: 200
                        body: Component {
                            Rectangle {
                                height: 50
                                color: "red"
                            }
                        }
                    }
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
}
