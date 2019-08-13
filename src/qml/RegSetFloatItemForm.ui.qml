import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Item {
    width: 400
    height: 40

    property alias input: input
    property alias msgTxt: msgTxt
    property alias setBtn: setBtn

    RowLayout {
        anchors.fill: parent

        TextField {
            id: input
            Layout.preferredWidth: parent.width * 1 / 3
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            font.pixelSize: 20
            selectByMouse: true
        }

        Text {
            id: msgTxt
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
            verticalAlignment: Text.AlignVCenter
        }
        Button {
            id: setBtn
            Layout.preferredWidth: parent.width * 1 / 3
            Layout.preferredHeight: parent.height
            text: "设置"
        }
    }
}
