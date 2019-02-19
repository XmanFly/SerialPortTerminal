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
            //            bottom: parent.bottom
            leftMargin: 10
        }
        width: parent.width * 1 / 8

        //下拉列表
        Repeater {
            id: cfgParaRpt
            model: 3
            delegate: ComboBox {
                id: eachItem
                //                height: itemHeight
                //                textRole: model.modelData.value:w
            }
        }
        RoundButton {
            id: switchBtn
            text: "开始"
            Layout.preferredWidth: 100
        }
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
