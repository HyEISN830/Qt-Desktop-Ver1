import QtQuick
import QtQuick.Controls
import AppQml

ToolTip {
    property string donestr: "Successed!"

    id: root
    y: -28
    delay: 500

    contentItem: Rectangle {
        color: "transparent"

        Text {
            id: txt
            text: root.text
            wrapMode: Text.Wrap
            color: Consts.tipFontColor
            font.pixelSize: 16
            font.family: Consts.fontBold

            ComDelay {
                id: delay
                visible: false
                width: 0
                height: 0
            }
        }

        SequentialAnimation {
            id: txtAniStage1

            onFinished: {
                delay.delay(1000, () => {
                    txtAniStage2.start()
                })
                txt.text = root.donestr
            }


            OpacityAnimator {
                target: txt;
                from: 1;
                to: 0;
                duration: 200
            }

            OpacityAnimator {
                target: txt;
                from: 0;
                to: 1;
                duration: 100
            }
        }

        SequentialAnimation {
            id: txtAniStage2

            onFinished: {
                txt.text = root.text
                txtAniStage3.start()
            }

            OpacityAnimator {
                target: txt;
                from: 1;
                to: 0;
                duration: 300
            }
        }

        SequentialAnimation {
            id: txtAniStage3

            OpacityAnimator {
                target: txt;
                from: 1;
                to: 1;
                duration: 300
            }
        }
    }

    function done() {
        txtAniStage1.start()
    }
}
