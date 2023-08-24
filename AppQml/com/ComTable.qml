import QtQuick
import QtQuick.Controls
import AppQml

Item {
    property var columns: []    // data struct {"name": "columnDisplayName", "width": columnWidth, "alias": "columnRealName"}, {"name": "#", "width": width, "alias": "#"} = 自动生成的序列
    property int columnHeight: 40
    property string columnColor: "#49bdc3c7"

    property var rows: []   // do not modify
    property int rows_len: rows.length
    property int rowHeight: 42

    property string rowColor: "#bdc3c7"         // row 默认颜色
    property string hoveredColor: "#4ea1de"     // row 鼠标悬浮颜色

    property var copycb: null // 双击复制 callback, parameter: string - 想要复制的内容

    property list<int> h_ws: []
    property int h_aws: 0

    /*
        data struct for "m_row":
        [
            {
                "rowIndex": real,   // index of row property
                "rowData": var      // data of row property, like this: {"column": "columnValue"}
            }
        ]
    */
    property var m_row: []
    property int m_row_len: m_row.length

    property bool enablePageLimiter: true
    property int curPage: 1
    property int rowCount: 0
    property int pageSize: compagesizes.currentValue
    property list<int> pageSizes: [20, 30, 50]
    property int pageLimiterHeight: 40
    property string pageLimiterColor: "#bdc3c7"
    property string pageLimiterHoveredColor: "#4ea1de"
    property int pagePrevBtnWidth: 40
    property int pagePrevBtnHeight: 40
    property int pageNextBtnWidth: 40
    property int pageNextBtnHeight: 40
    property int pageGotoBtnWidth: 40
    property int pageGotoBtnHeight: 40
    property string pageSizeSuffix: "条/页"
    property string prevPageDesc: "上一页"
    property string nextPageDesc: "下一页"
    property string gotoPageDesc: "前往"
    property string gotoPageDescSuffix: "页"

    property string fieldCopyDesc: "(双击复制)"
    property string fieldCopyDoneDesc: "已复制!"

    property int m_pages: parseInt((rowCount % pageSize) == 0 ? rowCount / pageSize : parseInt(rowCount / pageSize) + 1)

    property var pageChangedCb: null    // 页码改变时callback

    Rectangle {
        id: root
        anchors.fill: parent
        anchors.bottomMargin: pageLimiterHeight

        ScrollView {
            id: mainScrollView
            width: root.width
            height: root.height
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff

            Column {
                width: root.width

                ComPane {
                    id: headerPane

                    Rectangle {
                        id: headerbgcolor
                        color: columnColor
                        radius: height * 0.08
                    }

                    Row {
                        id: header
                        anchors.fill: parent

                        Repeater {
                            model: columns

                            Rectangle {
                                id: repeatRect
                                required property var modelData
                                required property int index

                                color: "transparent"
                                height: columnHeight
                                width: modelData.width ? modelData.width : columns[index].width = colText.width + 20

                                ComTextEdit {
                                    id: colText
                                    font.bold: true
                                    font.pixelSize: 15
                                    readOnly: true
                                    text: modelData.name
                                    anchors.centerIn: parent
                                }
                            }
                        }
                    }
                }

                Rectangle { // 行header 与 content 之间占位元素
                    id: headercontentwhite
                    height: headerPane.height + 7
                    width: root.width
                    z: -3
                    color: "transparent"
                }

                ComPane {
                    topPadding: 0
                    height: root.height - headerPane.height - headercontentwhite.height

                    ScrollView {
                        id: rowcontentView
                        height: parent.height
                        width: headerbgcolor.width + 16
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                        Column {
                            spacing: .5

                            Repeater {
                                model: rows_len

                                Row {
                                    id: renderrow
                                    required property var modelData
                                    required property int index
                                    property bool hovered: false

                                    Repeater {
                                        model: columns

                                        Rectangle {
                                            required property var modelData
                                            required property int index
                                            property bool isserial: columns[cell.index]["alias"] === "#"

                                            id: cell
                                            width: celltext.width
                                            height: rowHeight

                                            ComTextEdit {
                                                property bool hovered: false

                                                id: celltext
                                                width: columns[index].width
                                                height: rowHeight - 2
                                                text: cell.isserial ? renderrow.index + 1 : rows[renderrow.index][columns[cell.index]["alias"]]
                                                horizontalAlignment: TextEdit.AlignHCenter
                                                verticalAlignment: TextEdit.AlignVCenter

                                                ComToolTip {
                                                    id: cellTip
                                                    y: -28
                                                    delay: 500
                                                    visible: !cell.isserial && parent.hovered
                                                    text: celltext.text + fieldCopyDesc
                                                    donestr: fieldCopyDoneDesc
                                                }

                                                MouseArea {
                                                    anchors.fill: parent
                                                    hoverEnabled: true
                                                    onEntered: {
                                                        renderrow.hovered = true
                                                        parent.hovered = true
                                                    }
                                                    onExited: {
                                                        renderrow.hovered = false
                                                        parent.hovered = false
                                                    }
                                                    onDoubleClicked: {
                                                        if (cell.isserial) return false
                                                        if (copycb) copycb(celltext.text)
                                                        cellTip.done()
                                                    }
                                                }
                                            }

                                            Rectangle {
                                                y: celltext.height
                                                color: renderrow.hovered ? hoveredColor : rowColor
                                                height: 2
                                                width: celltext.width
                                                z: 1
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Rectangle {
        // debug背景色块
        y: root.height
        height: pageLimiterHeight
        width: root.width
        color: "yellow"
        z: -2
        visible: false
    }

    Row {
        y: root.height
        height: pageLimiterHeight
        spacing: 8
        x: h_aws - width + 11
        z: 1
        visible: enablePageLimiter

        ComboBox {
            id: compagesizes
            height: 35
            model: pageSizes
            anchors.bottom: lblpages.bottom
            anchors.bottomMargin: -5
            padding: 0
            width: 80
            onCurrentValueChanged: {
                if (curPage == 1) {
                    // 手动触发 pageChangedCb, 防止 pageSize 改变时, onCurPageChanged 未作响应;
                    // pageSize 为 0 时, 不应触发 callback, 否则可能为逻辑漏洞
                    // 为防止 pageSize = 0, 使用 compagesizes.currentValue 替代, 以获取到准确 "pageSize"
                    if (pageChangedCb && pageSize) pageChangedCb(curPage, compagesizes.currentValue)
                    return false
                }
                curPage = 1
            }
        }

        ComLabel {
            text: pageSizeSuffix
            anchors.bottom: lblpages.bottom
            font.pixelSize: lblpages.font.pixelSize
        }

        Rectangle {
            // 占位元素
            height: pageLimiterHeight
            width: 10
            color: "transparent"
        }

        ComLabel {
            id: lblpages
            text: `${curPage} / ${m_pages}`
            anchors.bottom: btnprev.bottom
            anchors.bottomMargin: 4
            rightPadding: 7
            font.pixelSize: 15
        }

        RoundButton {
            id: btnprev
            height: pagePrevBtnHeight
            width: pagePrevBtnWidth
            icon.source: "../resources/icon-angle-left.svg"
            enabled: curPage - 1

            onClicked: {
                if (curPage - 1) curPage--
            }

            ComToolTip {
                y: -47
                delay: 500
                visible: parent.hovered
                text: prevPageDesc
            }            
        }

        RoundButton {
            id: btnnext
            height: pageNextBtnHeight
            width: pageNextBtnWidth
            icon.source: "../resources/icon-angle-right.svg"
            enabled: m_pages && curPage != m_pages

            onClicked: {
                if (curPage + 1 <= m_pages) curPage++
            }

            ComToolTip {
                y: -47
                delay: 500
                visible: parent.hovered
                text: nextPageDesc
            }
        }

        Rectangle {
            // 占位元素
            height: pageLimiterHeight
            width: 20
            color: "transparent"
        }

        ComTextField {
            id: txtgotonnumber
            placeholderText: gotoPageDesc
            height: pageLimiterHeight - 10
            width: 65
            anchors.verticalCenter: btngoto.verticalCenter
        }

        RoundButton {
            id: btngoto
            height: pageGotoBtnHeight
            width: pageGotoBtnWidth
            icon.source: "../resources/icon-location.svg"
            enabled: txtgotonnumber.text.length && !isNaN(txtgotonnumber.text)
            onClicked: {
                if (m_pages)
                    curPage = parseInt(txtgotonnumber.text)
            }

            ComToolTip {
                y: -47
                delay: 500
                visible: parent.hovered
                text: parent.enabled ? `${gotoPageDesc} ${parseInt(txtgotonnumber.text)} ${gotoPageDescSuffix}` : "..."
            }
        }
    }

    onCurPageChanged: {
        if (pageChangedCb) pageChangedCb(curPage, pageSize)
    }

    function append(rowdata) {
        rows.push(rowdata)
        _rows_modified()
    }

    function overwrite(rs) {
        clear()
        rows = rs
        _rows_modified()
    }

    function pop() {
        rows.pop()
        _rows_modified()
    }

    function length() {
        return rows.length
    }

    function modify(rowIndex, newObject) {
        let _swap = []

        for (let i in rows)
            _swap.push(rows[i])

        clear()
        rows = _swap
        rows[rowIndex] = newObject
        _rows_modified()
    }

    function indexOf(rowIndex) {
        return rows[rowIndex]
    }

    function clear() {
        while (rows.length)
            rows.pop()
        _rows_modified()
    }

    function _rows_modified() {
        rows_len = rows.length
    }

    Component.onCompleted: {
        let bgwidth = 0
        let bgheight = 0
        let i = 0

        for (let item in header.children) {
            if (!(header.children[item] instanceof Rectangle)) continue
            if (header.children[item].width) {
                bgwidth += header.children[item].width
                h_ws[i] = header.children[item].width
                h_aws += header.children[item].width
            }
            if (header.children[item].height && !bgheight) bgheight = header.children[item].height
            i++
        }

        headerbgcolor.width = bgwidth
        headerbgcolor.height = bgheight

        if (!enablePageLimiter) pageLimiterHeight = 0
    }
}
