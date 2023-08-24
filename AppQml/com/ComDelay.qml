import QtQuick
import QtQuick.Controls

Item {
    property var cb: null
    property bool called: true

    id: mainItem

    Timer {
        id: timer

        onTriggered: {
            if (!cb || called) return false
            called = true
            cb()
        }
    }

    function delay(millisecond, callback) {
        timer.interval = millisecond
        timer.repeat = false
        cb = callback
        called = false
        timer.start()
    }

    function cancel() {
        timer.stop();
    }
}
