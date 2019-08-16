import QtQuick 2.13
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0
import SerialPortTerminal.DataObject 1.0
import SerialPortTerminal.TableModel 1.0
import SerialPortTerminal.FormatModel 1.0

/* LOG区域 */
GroupBox {
    id: root
    title: qsTr("数据显示区")
    width: 480
    height: 800

    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 10

        ListView {
            id: dataListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            interactive: true
            cacheBuffer: 10000
            clip: true
            delegate:
                RowLayout {
                    TextEdit {
                        text: Time
                        font {
                            pointSize: 12
                        }
                        width: parent.width
                        color: "teal"
                        selectByMouse: true
                    }
                    TextEdit {
                        text: Type
                        font {
                            pointSize: 12
                        }
                        color: Type === qsTr("发送") ? "darkorange" : "fuchsia"
                    }
                    TextInput {
                        text: Data
                        width: parent.width
                        font {
                            pointSize: 12
                        }
                        selectByMouse: true
                    }
                    ListView.onAdd: {
                        dataListView.positionViewAtEnd()
                    }
                }

            ScrollBar.vertical: ScrollBar {
                id: listVerticalScrBar
                interactive: true
                policy: ScrollBar.AlwaysOn
                width: 20
                minimumSize: 0.2
            }
            ScrollBar.horizontal: ScrollBar {
                height: 20
                minimumSize: 0.3
            }

            onCurrentItemChanged: {
            }
            onCountChanged: {
            }
            onContentYChanged: {
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
                        dataListView.model.clear()
                        console.log("refresh " + "length " + dataListView.contentItem.children.length)
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

    function setModel(mModel){
        dataListView.model = mModel
        console.log("receive aera set model " + mModel)
    }

    //设置显示格式model
    function setFormatModel(mModel){
        formatRect.fomatRpt.model = mModel
    }
}
