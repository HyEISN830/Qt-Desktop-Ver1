import QtQuick
import QtQuick.Controls
import Qt.labs.qmlmodels
import AppQml
import AppQmlBackend

import "js/Common.js" as Common

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

    OpacityAnimator {
        target: page;
        from: 0;
        to: 1;
        duration: 600
        running: view.currentItem == page
    }

    Component.onCompleted: {
    }
}
