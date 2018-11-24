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

        ScrollView {
            property int initHeight: parent.height * 8 / 10
            property int initWidth: parent.width
            property int listViewRealHeight : initHeight  //listview实时高度
            property int listViewRealWidth : initWidth //listview实时宽度

            id: dataFlick
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 8 / 10
//                        anchors {
//                            bottom: parent.bottom
//                        }
            clip: true
//            boundsBehavior: Flickable.StopAtBounds
//            contentWidth: listViewRealWidth
//            contentHeight: listViewRealHeight
//            contentY : contentHeight-height //定位至最后一行
//            contentHeight: cl.height


            ColumnLayout {
                id: cl
                anchors {
//                    top: parent.bottom
                    bottom: parent.bottom
//                    bottomMargin: - dataFlick.height
                }
//                layoutDirection: Qt.RightToLeft
                Repeater {
                    id: dataListView

                    delegate:
                        RowLayout {
//                        anchors {
//                            bottom:  dataFlick.bottom
//                        }
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
                            text: model.modelData.value
                            width: parent.width
                            font {
                                pointSize: 12
                            }
                            selectByMouse: true
        //                onClicked: console.log("clicked:", modelData)
                        }
                    }
                    onCountChanged: {
                        dataFlick.moveToEnd()
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {
                id: vBar
                width: 20
                anchors {
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                onSizeChanged: {
//                    position = 1
                }
                policy: ScrollBar.AlwaysOn
                minimumSize: 0.3
            }
            ScrollBar.horizontal: ScrollBar {
                height: 20
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                minimumSize: 0.3
            }

            //调整显示区定时器
            Timer {
                id: rcvAeraAjustTimer;
                interval: 500;
                running: false;
                repeat: false;
                triggeredOnStart: false;
                onTriggered:{
                    dataListView.rcvAeraAjust()
                    console.log("rcvAeraAjustTimer trigger ")
                }
            }

            //定位至最后
            function moveToEnd(){
                cl.anchors.bottom = cl.parent.bottom
//                dataListView.itemAt(dataListView.count-1).x = 100
//                var realHeight = 0
//                for(var child in dataListView.children){
//                    realHeight += dataListView.children[child].height
//                    console.log("dataFlick child " , dataFlick.contentChildren[child].text)
//                }
//                for(var child in dataListView.count){
//                    realHeight += dataListView.itemAt(child).height
//                    console.log("dataFlick child " , dataListView.itemAt(child).height)
//                }
//                console.log("move to end " + dataListView.count
//                            + "  " + realHeight
//                            + "  " + cl.height)
//                dataFlick.contentHeight = realHeight
//                vBar.position = 0.8
//                dataFlick.y = dataFlick.contentHeight-dataFlick.height //定位至最后一行
//                dataListView.positionViewAtEnd()
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
                        mInterface.clearDataModel()
//                        dataFlick.listViewRealHeight = dataFlick.initHeight
//                        dataFlick.listViewRealWidth = dataFlick.initWidth
//                        console.log("refresh "
//                                    + "length " + dataListView.contentItem.children.length )
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
//        dataFlick.moveToEnd()
    }

    //设置显示格式model
    function setFormatModel(mModel){
        formatRect.fomatRpt.model = mModel
    }
}
