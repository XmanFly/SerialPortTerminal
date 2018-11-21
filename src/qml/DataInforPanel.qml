import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0

/* 数据信息面板 */
GroupBox {
    id: root

    title: qsTr("数据统计")
    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 20
        Repeater {
            model: ListModel {
                ListElement { name: "接收" }
                ListElement { name: "发送" }
            }
            CntItem {
                itemName: name
            }
        }
    }
}
