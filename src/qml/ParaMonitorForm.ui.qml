import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Item {
    width: 400
    height: 400

    property alias paraList: paraList

    GroupBox {
        anchors.fill: parent
        title: qsTr("参数监测")
        ListView {
            id: paraList
            anchors.fill: parent
            clip: true
            delegate: Rectangle {
                height: 30
                width: parent.width
                RowLayout {
                    id: nameRow
                    anchors {
                        left: parent.left
                        top: parent.top
                        bottom: parent.bottom
                    }
                    width: parent.width * 0.3
                    Text {
                        text: name
                    }
                }
                RowLayout {
                    id: itemRow
                    anchors {
                        right: parent.right
                        top: parent.top
                        bottom: parent.bottom
                    }
                    width: parent.width * 0.7
                    Text {
                        text: value.toFixed(1)
                        horizontalAlignment: Text.AlignRight
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.preferredWidth: parent.width * 0.5
                    }
                    Text {
                        text: unit
                        horizontalAlignment: Text.AlignRight
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.preferredWidth: 10
                    }
                }
            }
        }
    }
}
