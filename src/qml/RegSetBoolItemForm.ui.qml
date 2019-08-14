import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Item {
    width: 400
    height: 40

    property alias input: input
    property alias msgTxt: msgTxt

    RowLayout {
        anchors.fill: parent

        Switch {
            id: input
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
        }
        Text {
            id: msgTxt
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
        }
    }
}
