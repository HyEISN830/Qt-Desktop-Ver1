
// return now DateTime
function now() {
    return new Date().toLocaleString(Qt.locale("zh_CN"), "yyyy-MM-dd hh:mm:ss")
}

function dateValid(dateTimeStr) {
    return new Date(dateTimeStr) == "Invalid Date"
}
