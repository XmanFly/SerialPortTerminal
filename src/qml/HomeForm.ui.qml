import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    width: 1366
    height: 768

    property alias dataInforPanel: dataInforPanel
    property alias ctrlPanel: ctrlPanel
    property alias sendAera: sendAera
    property alias receiveAera: receiveAera

    ColumnLayout {
        id: leftLayout
        anchors {
            left: parent.left
            leftMargin: 20
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 20
        }
        width: parent.width * 2 / 10
        spacing: 10

        //控制面板
        ControlPanel {
            id: ctrlPanel
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        }

        //数据信息
        DataInforPanel {
            id: dataInforPanel
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            implicitWidth: ctrlPanel.width
        }
    }

    //收发缓冲区
    ColumnLayout {
        id: dataAera
        anchors {
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 20
            left: leftLayout.right
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
