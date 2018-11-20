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
            flickableDirection:Flickable.HorizontalAndVerticalFlick
            clip: true

            ListView {
                id: dataListView
                orientation: ListView.Horizontal | ListView.Vertical
                anchors {
                    fill: parent
                }

    //            model: DataObject

                delegate:
                    RowLayout {
                        TextEdit {
                            text: model.modelData.time
                            font {
                                pointSize: 12
                            }
                            width: parent.width
                            color: "blue"
    //                onClicked: console.log("clicked:", modelData)
                    }
                    TextEdit {
                        text: "  "
                    }
                    TextEdit {
                        text: model.modelData.data
                        width: parent.width
                        font {
                            pointSize: 12
                        }
    //                onClicked: console.log("clicked:", modelData)
                    }
                }

                ScrollBar.vertical: ScrollBar {
                    width: 20
                }
                ScrollBar.horizontal: ScrollBar {
                    width: 20
                }
            }

            //            ScrollBar.horizontal: ScrollBar {
//                parent: dataFlick.parent
////                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
////                anchors.top: dataFlick.top
//                anchors.left: dataFlick.left
//                anchors.right: dataFlick.right
//                anchors.bottom: dataFlick.bottom
//            }
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
