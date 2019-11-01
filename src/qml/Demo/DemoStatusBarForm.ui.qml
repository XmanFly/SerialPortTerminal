import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Item {
    width: 400
    height: 400
    property alias statusLbl: statusLbl

    Rectangle {
        anchors.fill: parent
        color: "#002EB7"
    }

    DemoLabel {
        id: statusLbl
        anchors.centerIn: parent
        text: qsTr("就绪")
        font.pixelSize: 40
    }
}
