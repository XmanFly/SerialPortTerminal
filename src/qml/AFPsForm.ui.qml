import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtCharts 2.3

Page {
    width: 1366
    height: 768
    property alias chartRpt: chartRpt
    property alias switchBtn: switchBtn
    property alias cfgParaRpt: cfgParaRpt
    property alias fileExp: fileExp
    property alias paraMonitor: paraMonitor
    property alias userDefined: userDefined
    property alias algorithm: algorithm

    //数据文件加载区
    Explorer {
        id: fileExp
        anchors {
            top: parent.top
            left: parent.left
            bottom: ctrlPanel.top
            bottomMargin: 20
            leftMargin: 10
        }
        width: parent.width * 2 / 10
        z: 6
    }

    //控制区
    ColumnLayout {
        id: ctrlPanel
        anchors {
            left: fileExp.left
            bottom: parent.bottom
            bottomMargin: 20
        }
        width: fileExp.width * 0.6

        //下拉列表
        Repeater {
            id: cfgParaRpt
            Layout.fillWidth: true
            model: 3
            delegate: ComboBox {
                id: eachItem
                Layout.fillWidth: true

                popup: Popup {
                    y: eachItem.height - 1
                    width: eachItem.width
                    implicitHeight: contentItem.implicitHeight
                    padding: 1

                    contentItem: ListView {
                        clip: true
                        implicitHeight: contentHeight
                        model: eachItem.popup.visible ? eachItem.delegateModel : null
                        currentIndex: eachItem.highlightedIndex
                        ScrollBar.vertical: ScrollBar {
                            policy: ScrollBar.AlwaysOn
                        }
                    }

                    background: Rectangle {
                        border.color: "#21be2b"
                        radius: 2
                    }
                }
            }
        }
        TextArea {
            id: userDefined
            placeholderText: qsTr("输入自定义内容")
            color: "blue"
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            font {
                pointSize: 12
            }
            selectByMouse: true
            background: Rectangle {
                border.color: "green"
            }
        }
        RoundButton {
            id: switchBtn
            text: "开始"
            Layout.preferredWidth: 100
        }
    }

    ColumnLayout {
        id: algorLayout
        anchors {
            left: fileExp.right
            top: fileExp.top
            bottom: parent.bottom
            bottomMargin: 20
        }
        width: parent.width * 0.15
        spacing: 20
        //参数监测区
        ParaMonitor {
            id: paraMonitor
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        }
        //功能区
        Function {
            id: func
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.1
        }
        //算法区
        AfpsAlgorithm {
            id: algorithm
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    //绘图区
    ColumnLayout {
        id: chartAera
        anchors {
            left: algorLayout.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 20
        }
        Repeater {
            id: chartRpt
            model: 5
            AdChart {
                id: chart
                Layout.preferredHeight: chartAera.height / chartRpt.count
                Layout.preferredWidth: chartAera.width
            }
        }
    }
}






/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
