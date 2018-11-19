import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0

/* 接收区域 */
GroupBox {
    id: root
    title: qsTr("接收区")
    contentHeight: 100 //指定内容高度 防止循环绑定
    implicitWidth: 100 //指定宽度 防止循环绑定

    property bool sendEnable: false //发送使能

    signal sendData(string data) //发送数据

    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 10

        ListView {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 8 / 10

            model: Qt.fontFamilies()

            delegate: ItemDelegate {
                text: modelData
                width: parent.width
                onClicked: console.log("clicked:", modelData)
            }

            ScrollIndicator.vertical: ScrollIndicator {
//                Layout.width: 10
//                Layout.preferredWidth: 10
//                implicitWidth: 10
//                width: 6
            }
        }

        RowLayout {
            Layout.preferredWidth: parent.width
            //清空按钮
            RoundButton {
                id: clearRbtn
                implicitWidth: 100
                radius: 2
                text: qsTr("清空")
                onClicked: {
                    sendBuffer.clear()
                }
            }
        }
    }
}
