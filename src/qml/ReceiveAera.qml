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

        Flickable {
            property int initHeight: parent.height * 8 / 10
            property int initWidth: parent.width
            property int listViewRealHeight : initHeight  //listview实时高度
            property int listViewRealWidth : initWidth //listview实时宽度

            id: dataFlick
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 8 / 10
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            contentWidth: listViewRealWidth
            contentHeight: listViewRealHeight
            contentY : contentHeight-height //定位至最后一行

            ListView {
                id: dataListView
                interactive: true
                anchors {
                    fill: parent
                }
                cacheBuffer: 4000000

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
                        text: model.modelData.value
                        width: parent.width
                        font {
                            pointSize: 12
                        }
                        selectByMouse: true
    //                onClicked: console.log("clicked:", modelData)
                    }
                }
                onCurrentItemChanged: {
                }
                onCountChanged: {
                    rcvAeraAjustTimer.restart() //开启调整显示区定时器
                }
                onContentYChanged: {
                }

                //调整显示区
                function rcvAeraAjust(){
                    var curHeight = 0
                    var curWidth = 0
                    for(var child in dataListView.contentItem.children) {
                        if(dataListView.contentItem.children[child].width > curWidth){
                            curWidth = dataListView.contentItem.children[child].width
                        }
                    }
                    if(curWidth > dataFlick.initWidth){
                        dataFlick.listViewRealWidth = curWidth
                    }
                    console.log("rcvAeraAjust "
                                + "length " + dataListView.contentItem.children.length + " "
                                + dataFlick.listViewRealHeight + " "
                                + dataFlick.initHeight + " "
                                + dataFlick.listViewRealWidth + " "
                                + dataFlick.initWidth + " "
                                + curWidth + " "
                                + dataFlick.width + " ")
                }

                ScrollBar.vertical: ScrollBar {
                    id: listVerticalScrBar
                    interactive: true
                    width: 20
                    minimumSize: 0.2
                }
            }

            ScrollBar.horizontal: ScrollBar {
                height: 20
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
//                dataFlick.contentY = dataFlick.contentHeight-dataFlick.height //定位至最后一行
                dataListView.positionViewAtEnd()
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
                        dataFlick.listViewRealHeight = dataFlick.initHeight
                        dataFlick.listViewRealWidth = dataFlick.initWidth
                         console.log("refresh "
                                    + "length " + dataListView.contentItem.children.length )
                    }
                }
                ToolSeparator {}
                Rectangle {
                    id: formatRect
                    property int realWidth : 220
                    implicitWidth: realWidth
                    implicitHeight: controlLayout.height
//                    color: "red"
                    ButtonGroup {
                        id: buttonGroup
                    }
                    ListView {
                        id: fomatListView
                        anchors {
                            fill: parent
                        }
                        orientation: ListView.Horizontal
                        delegate: RadioDelegate {
                            id: rd
                            text: model.modelData.name
                            checked: index == 0
                            ButtonGroup.group: buttonGroup
                            Binding {
                                target: model.modelData
                                property: "isSelected"
                                value: rd.checked
                            }
                        }
                        Component.onCompleted: {
                            var curWidth = 0
                            var child
                            for(child in contentItem.children) {
                                if(contentItem.children[child].text){
                                    curWidth  += contentItem.children[child].width
                                }
                                console.log("formatrect name " + contentItem.children[child].text)
                            }
                            formatRect.realWidth = curWidth
                            console.log("formatrect width " + contentItem.children.length)
                        }
                    }
                }
                ToolSeparator {}
            }
        }
    }

    function setModel(mModel){
        dataListView.model = mModel
        dataFlick.moveToEnd()
    }

    //设置显示格式model
    function setFormatModel(mModel){
        fomatListView.model = mModel
    }
}
