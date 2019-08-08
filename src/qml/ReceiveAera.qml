import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0
import SerialPortTerminal.DataObject 1.0
import SerialPortTerminal.TableModel 1.0
import SerialPortTerminal.FormatModel 1.0

/* 接收区域 */
GroupBox {
    id: root
    width: 480
    height: 800
    clip: true
    title: qsTr("接收区")

    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 10

        ScrollView {
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            ScrollBar.horizontal: ScrollBar {
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }
                height: 20
                minimumSize: 0.1
            }
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOn
                anchors {
                    top:  parent.top
                    bottom: parent.bottom
                    right: parent.right
                }
                width: 20
                minimumSize: 0.1
            }
            TextArea {
                id: displayTxt
                anchors.fill: parent
            }
        }

        RowLayout {
            id: controlLayout
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 40
            RowLayout {
                //清空按钮
                RoundButton {
                    id: clearRbtn
                    implicitWidth: 100
                    radius: 2
                    text: qsTr("清空")
                    onClicked: {
                    }
                }
                ToolSeparator {}
                FormatSwitch {
                    id: formatRect
                }
                ToolSeparator {}
            }
        }
    }

    function add(data, mType){
        displayTxt.append(data)
    }

    function setTxt(data){
        displayTxt.text = data
    }

    //设置显示格式model
    function setFormatModel(mModel){
        formatRect.fomatRpt.model = mModel
    }
}
