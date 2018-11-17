import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    width: 1366
    height: 768

    property alias ctrlPanel: ctrlPanel

    ControlPanel {
        id: ctrlPanel
        anchors {
            left: parent.left
            top: parent.top
        }
        width: parent.width * 2 / 10
    }
}
