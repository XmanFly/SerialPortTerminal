import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0
import SerialPortTerminal.DataObject 1.0
import SerialPortTerminal.TableModel 1.0

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

        Flickable {
            id: dataFlick
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 8 / 10
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            contentWidth: parent.width * 20 //横向显示内容最大长度
            contentHeight: parent.height

            ListView {
                id: dataListView
                interactive: true
                anchors {
                    fill: parent
                }

                delegate:
                    RowLayout {
                        TextEdit {
                            text: model.modelData.time
                            font {
                                pointSize: 12
                            }
                            width: parent.width
                            color: "blue"
                            selectByMouse: true
    //                onClicked: console.log("clicked:", modelData)
                    }
                    TextEdit {
                        text: "  "
                    }
                    TextInput {
                        text: model.modelData.data
                        width: parent.width
                        font {
                            pointSize: 12
                        }
                        selectByMouse: true
    //                onClicked: console.log("clicked:", modelData)
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                width: 20
            }
            ScrollBar.horizontal: ScrollBar {
                height: 20
                minimumSize: 0.3
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
                    mInterface.clearDataModel()
                }
            }
        }
    }

    function setModel(mModel){
        dataListView.model = mModel
        dataListView.positionViewAtEnd()
    }
}
