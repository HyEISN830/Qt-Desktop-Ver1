
// return now DateTime
function now() {
    return new Date().toLocaleString(Qt.locale("zh_CN"), "yyyy-MM-dd hh:mm:ss")
}

function dateValid(dateTimeStr) {
    return new Date(dateTimeStr) == "Invalid Date"
}

function showDialog(parent, title, content, type, acceptCb, rejectCb) {
    let com = Qt.createComponent("../com/ComDialog.qml");
    let dialog = com.createObject(parent, { title, content, type, acceptCb, rejectCb });
    dialog.open();
}
