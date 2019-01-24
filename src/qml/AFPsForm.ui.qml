import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.3

Page {
    width: 1366
    height: 768
    property alias chartRpt: chartRpt
    property alias switchBtn: switchBtn

    //控制区
    ColumnLayout {
        id: ctrlPanel
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width: parent.width * 1 / 8

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
