import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.3

Page {
    width: 1366
    height: 768
    property alias stopBtn: stopBtn
    property alias startBtn: startBtn

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
            id: startBtn
            text: "开始"
            Layout.preferredWidth: 100
        }
        RoundButton {
            id: stopBtn
            text: "停止"
            Layout.preferredWidth: 100
        }
    }

    //绘图区
    ColumnLayout {
        anchors {
            left: ctrlPanel.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        ChartView {
            id: channel1
            backgroundRoundness: 3
            theme: ChartView.ChartThemeLight
            //            legend.visible: false //关闭图例
            antialiasing: true //抗锯齿
        }
        ChartView {
            id: channel2
        }
        ChartView {
            id: channel3
        }
        ChartView {
            id: channel4
        }
    }
}
