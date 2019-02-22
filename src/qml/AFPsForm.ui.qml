import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.3

Page {
    width: 1366
    height: 768
    property alias chartRpt: chartRpt
    property alias switchBtn: switchBtn
    property alias cfgParaRpt: cfgParaRpt

    //控制区
    ColumnLayout {
        id: ctrlPanel
        anchors {
            left: parent.left
            top: parent.top
            leftMargin: 10
        }
        width: parent.width * 2 / 8

        //下拉列表
        Repeater {
            id: cfgParaRpt
            model: 3
            delegate: ComboBox {
                id: eachItem

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
        RoundButton {
            id: switchBtn
            text: "开始"
            Layout.preferredWidth: 100
        }
    }

    //数据文件加载区
    Explorer {
        anchors {
            top: ctrlPanel.bottom
            left: ctrlPanel.left
            right: ctrlPanel.right
            bottom: parent.bottom
            bottomMargin: 20
        }
//        folder: "Data"
    }

    //绘图区
    ColumnLayout {
        id: chartAera
        anchors {
            left: ctrlPanel.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        Repeater {
            id: chartRpt
            model: 4
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
