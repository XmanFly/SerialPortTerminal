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
        anchors {
            fill: parent
            topMargin: 20
        }
        currentIndex: tabBar.currentIndex
        interactive: false

        Home {
            id: home
        }
//        Page1Form{
//        }

        AFPs {
            id: afps

//            onSig_start : {
//                mInterface.afpsStart()
//            }
//            onSig_stop : {
//                mInterface.afpsStop()
//            }
        }
    }

    header: TabBar {
        id: tabBar
        implicitHeight: 40
        currentIndex: swipeView.currentIndex

        TabButton {
            implicitHeight: parent.height
            text: qsTr("主页")
            background: Rectangle{
                color: tabBar.currentIndex === 0 ? "lightblue" : "gray"
            }
        }
        TabButton {
            implicitHeight: parent.height
            text: qsTr("荧光")
            background: Rectangle{
                color: tabBar.currentIndex === 1 ? "lightblue" : "gray"
            }
        }
    }

    Component.onCompleted: {
        home.setInterface(mInterface)        
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

    //荧光
    Connections {
        target: mInterface
        onSig_afpsUpdateChart : {
            mInterface.afpsUpdateChart(afps.channel1Chart.updateSeries(0), afps.channel2Chart.updateSeries(0),
                                       afps.channel3Chart.updateSeries(0), afps.channel4Chart.updateSeries(0))
        }
    }
    Connections {
        target: afps
        onSig_start : {
            mInterface.afpsStart()
        }
        onSig_stop : {
            mInterface.afpsStop()
        }        
    }
}
