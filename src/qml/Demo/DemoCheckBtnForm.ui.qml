import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

RoundButton {
    id: antiShakeBtn
    width: 1300
    height: 80
    radius: 100
    property var txt: ""
    property var fontSize: 30
    property var bkColor: "#002EB7"
    contentItem: DemoLabel {
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: txt
        font.pixelSize: fontSize
    }
    background: Rectangle {
        radius: 100
        color: antiShakeBtn.pressed ? "#B4B4B4" : bkColor
    }
}
