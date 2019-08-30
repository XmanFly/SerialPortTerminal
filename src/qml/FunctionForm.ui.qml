import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

GroupBox {
    width: 400
    height: 400

    property alias cleanBtn: cleanBtn

    title: qsTr("功能区")

    ColumnLayout {
        anchors.fill: parent

        RoundButton {
            id: cleanBtn
            radius: 5
            Layout.preferredWidth: 80
            text: qsTr("清洗")
        }
    }
}
