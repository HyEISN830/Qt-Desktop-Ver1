import QtQuick

Item {
    property bool open: false
    property string openStr: "TRUE"
    property string closeStr: "FALSE"

    id: toggle

    Rectangle {
        height: 40
        width: body.width
        color: "transparent"

        MouseArea {
            anchors.fill: parent
            onClicked: toggle.open = !toggle.open
        }

        Rectangle {
            id: icon
            width: 40
            height: 40
            radius: height

            Image {
                id: iconImg
                anchors.centerIn: parent
                width: 20
                height: 20
                mipmap: true
                source: "../resources/icon-play.svg"
            }

            RotationAnimation {
                target: iconImg
                running: toggle.open
                from: 0
                to: 360
                duration: 500
            }

            PropertyAnimation {
                target: icon
                running: toggle.open
                property: "x"
                duration: 500
                to: body.width - icon.width
            }

            OpacityAnimator {
                target: iconImg
                running: toggle.open
                from: 1
                to: 0
                duration: 500
                onFinished: {
                    iconImg.source = "../resources/icon-pause.svg"
                    onOpenAni.start()
                }
            }

            ColorAnimation on color {
                running: toggle.open
                to: "#2ecc71"
                duration: 500
                easing.type: Easing.OutCubic
            }

            OpacityAnimator {
                id: onOpenAni
                target: iconImg
                from: 0
                to: 1
                duration: 200
            }

            RotationAnimation {
                target: iconImg
                running: !toggle.open
                from: 360
                to: 0
                duration: 500
            }

            PropertyAnimation {
                target: icon
                running: !toggle.open
                property: "x"
                duration: 500
                to: 0
            }

            OpacityAnimator {
                target: iconImg
                running: !toggle.open
                from: 1
                to: 0
                duration: 500
                onFinished: {
                    iconImg.source = "../resources/icon-play.svg"
                    unOpenAni.start()
                }
            }

            OpacityAnimator {
                id: unOpenAni
                target: iconImg
                from: 0
                to: 1
                duration: 200
            }

            ColorAnimation on color {
                running: !toggle.open
                to: "#e74c3c"
                duration: 500
                easing.type: Easing.OutCubic
            }
        }

        Rectangle {
            id: body
            width: (icon.width * 1.5) + content.width
            height: parent.height
            radius: height / 2
            z: icon.z - 1

            ColorAnimation on color {
                running: !toggle.open
                to: "#c0392b"
                duration: 500
                easing.type: Easing.OutCubic
            }

            ColorAnimation on color {
                running: toggle.open
                to: "#27ae60"
                duration: 500
                easing.type: Easing.OutCubic
            }

            ComTextEdit {
                id: content
                readOnly: true
                anchors.verticalCenter: parent.verticalCenter
                x: icon.width + 5
                font.pixelSize: 15
                color: "white"

                ColorAnimation on color {
                    id: unOpenCAni
                    to: "white"
                    duration: 200
                    easing.type: Easing.OutCubic
                }

                ColorAnimation on color {
                    id: onOpenCAni
                    to: "black"
                    duration: 200
                    easing.type: Easing.OutCubic
                }

                PropertyAnimation {
                    target: content
                    running: toggle.open
                    property: "x"
                    duration: 500
                    to: (icon.width / 2) - 5
                }

                OpacityAnimator {
                    target: content
                    running: toggle.open
                    to: 0
                    duration: 400
                    onFinished: {
                        content.text = toggle.openStr
                        onOpenCAni.start()
                        onContentAni.start()
                    }
                }

                OpacityAnimator {
                    id: onContentAni
                    target: content
                    duration: 200
                    to: 1
                }

                PropertyAnimation {
                    target: content
                    running: !toggle.open
                    property: "x"
                    duration: 500
                    to: icon.width + 5
                }

                OpacityAnimator {
                    target: content
                    running: !toggle.open
                    to: 0
                    duration: 400
                    onFinished: {
                        content.text = toggle.closeStr
                        unOpenCAni.start()
                        unContentAni.start()
                    }
                }

                OpacityAnimator {
                    id: unContentAni
                    target: content
                    duration: 200
                    to: 1
                }
            }
        }
    }
}
