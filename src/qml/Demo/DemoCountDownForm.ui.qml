import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Item {
    width: 800
    height: 800

    //        property var maxRadius: width > height ? height : width
    property var maxRadius: 500
    property var iColor: "#002EB7"

    //外圈
    Rectangle {
        anchors.centerIn: parent
        width: maxRadius
        height: maxRadius
        radius: width * 0.5
        antialiasing: true
        color: "white"
        border {
            color: iColor
            width: 1
        }
    }
    //内圈
    Rectangle {
        anchors.centerIn: parent
        width: maxRadius - 100
        height: maxRadius - 100
        radius: width * 0.5
        antialiasing: true
        color: "white"
        border {
            color: iColor
            width: 1
        }
    }
    FontMetrics {
        id: metrics
        font: checkTimeLbl.font
    }
    //检出时间文字
    Text {
        id: checkTimeLbl
        anchors.centerIn: parent
        bottomPadding: -20
        color: iColor
        font.pixelSize: 180
        text: qsTr("10")
        verticalAlignment: Text.AlignBottom
    }
    //时间单位
    DemoLabel {
        anchors {
            left: checkTimeLbl.right
            bottom: checkTimeLbl.bottom
        }
        color: iColor
        font.pixelSize: 40
        text: qsTr("s")
        verticalAlignment: Text.AlignBottom
    }
    //检出时间说明
    DemoLabel {
        anchors {
            top: checkTimeLbl.bottom
            horizontalCenter: checkTimeLbl.horizontalCenter
        }
        color: iColor
        font.pixelSize: 20
        text: qsTr("检出时间")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }
}
