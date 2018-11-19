import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0

/* 发送区域 */
GroupBox {
    id: root
    title: qsTr("发送区")
    contentHeight: 100 //指定内容高度 防止循环绑定
    implicitWidth: 100 //指定宽度 防止循环绑定

    property bool sendEnable: false //发送使能

    signal sendData(string data) //发送数据

    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 10

        ScrollView {
            id: view
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 8 / 10
            TextArea {
                id: sendBuffer
                placeholderText: qsTr("输入发送字符")
                color: "blue"
                font {
                    pointSize: 12
                }
                background :
                    Rectangle {
                        anchors.fill: parent
//                        color: "lightgray"
                    }
            }
        }

        RowLayout {
            Layout.preferredWidth: parent.width
            //发送按钮
            RoundButton {
                id: sendRbtn
                implicitWidth: 100
                radius: 2
                text: qsTr("发送")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                enabled: sendEnable
                onClicked: {
                    sendData(sendBuffer.text)
                }
            }
        }
    }
}
