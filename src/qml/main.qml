import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1366
    height: 768
    title: qsTr("Tabs")

    Interface {
        id: mInterface
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Home {
            id: home

        }
//        Page1Form{
//        }

        Page2Form {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }

    Component.onCompleted: {
//        home.setInterface(mInterface)
    }

    Connections {
        target: mInterface
        onSig_message : {
            //创建消息弹窗
            var msgDlg = Qt.createQmlObject("import QtQuick 2.9; import QtQuick.Dialogs 1.1;"
                                            + "MessageDialog {property alias msgDlg : msgDlg; id: msgDlg; onAccepted : {} Component.onCompleted: visible = true}", root)
            msgDlg.msgDlg.text = msg
            msgDlg.msgDlg.icon = StandardIcon.Warning
        }
    }
}
