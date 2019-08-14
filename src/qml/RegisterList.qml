import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Page {
    width: 1920
    height: 1080

    property var name
    property var regModel

    GroupBox {
        title: name
        anchors.fill: parent

        ScrollView {
            anchors.fill: parent
            clip: true

            Column {
                anchors.fill: parent
                spacing: 20
                Repeater {
                    model: regModel

                    RWRegItem {
                    }
                }
            }
        }
    }
}
