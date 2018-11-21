import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3


/* 显示个数 */
Rectangle {
    height: 30
    Layout.fillWidth: true

    property alias itemName: name.text
    property alias cnt: cnt.text
    property alias clear: clear

    RowLayout {
        anchors {
            fill: parent
        }
        Text {
            id: name
            text: qsTr("text")
        }
        Text {
            id: cnt
            Layout.fillWidth: true
            text: qsTr("text")
            horizontalAlignment: Text.AlignRight
        }
        RoundButton {
            id: clear
            radius: 2
            implicitWidth: 100
            text: qsTr("清零")
        }
    }
}
