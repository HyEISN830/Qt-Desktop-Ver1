import QtQuick
import AppQml

TextEdit {
    id: textEdit

    font.pixelSize: 14
    font.family: Consts.fontBold
    font.weight: 545
    verticalAlignment: Text.AlignVCenter
    selectByMouse: true
    readOnly: true
    selectByKeyboard: false
    mouseSelectionMode: TextInput.SelectCharacters
}
