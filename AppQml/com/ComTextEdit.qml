import QtQuick
import AppQml

TextEdit {
    id: textEdit

    font.pixelSize: 14
    font.bold: false
    font.family: Consts.fontNormal
    verticalAlignment: Text.AlignVCenter
    selectByMouse: true
    readOnly: true
    selectByKeyboard: false
    mouseSelectionMode: TextInput.SelectCharacters

}
