import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtCharts 2.3

Page {
    width: 1366
    height: 768
    property alias channel4Chart: channel4
    property alias channel3Chart: channel3
    property alias channel2Chart: channel2
    property alias channel1Chart: channel1
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
        id: chartAera
        anchors {
            left: ctrlPanel.right
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }
        AdChart {
            id: channel1
            Layout.preferredHeight: chartAera.height / 4
            Layout.preferredWidth: chartAera.width
        }
        AdChart {
            id: channel2
            Layout.preferredHeight: chartAera.height / 4
            Layout.preferredWidth: chartAera.width
        }
        AdChart {
            id: channel3
            Layout.preferredHeight: chartAera.height / 4
            Layout.preferredWidth: chartAera.width
        }
        AdChart {
            id: channel4
            Layout.preferredHeight: chartAera.height / 4
            Layout.preferredWidth: chartAera.width
        }
    }
}
