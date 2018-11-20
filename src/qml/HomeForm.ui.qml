import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    width: 1366
    height: 768

    property alias ctrlPanel: ctrlPanel
    property alias sendAera: sendAera
    property alias receiveAera: receiveAera

    //控制面板
    ControlPanel {
        id: ctrlPanel
        anchors {
            left: parent.left
            leftMargin: 20
            top: parent.top
        }
        width: parent.width * 2 / 10
    }
    //收发缓冲区
    ColumnLayout {
        id: dataAera
        anchors {
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 20
            left: ctrlPanel.right
            leftMargin: 20
            right: parent.right
            rightMargin: 20
        }
        ReceiveAera {
            id: receiveAera
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 3 / 5
        }
        SendAera {
            id: sendAera
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height * 2 / 5
        }
    }
}
