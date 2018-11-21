import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

/* 显示个数 */
Rectangle {
    height: 30
    Layout.fillWidth: true

    signal clearCnt()

    property alias itemName: name.text
    property alias cnt: cnt.text

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
            text: qsTr("text")
        }
        RoundButton {
            id: clear
            radius: 2
            implicitWidth: 100
            text: qsTr("清零")
            onClicked: {
                clearCnt();
            }
        }
    }
}
