import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Item {
    width: 400
    height: 40

    property alias value: value
    property alias msgTxt: msgTxt
    property alias readBtn: readBtn

    RowLayout {
        anchors.fill: parent

        Switch {
            id: value
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
            enabled: false
        }
        Text {
            id: msgTxt
            verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
        }
        Button {
            id: readBtn
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
        }
    }
}
