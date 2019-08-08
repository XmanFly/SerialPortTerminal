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

//    Interface {
//        id: mInterface
//    }

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
            text: qsTr("端口")
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


    Connections {
        target: mInterface
        onSig_message : {
            //创建消息弹窗
            var msgDlg = Qt.createQmlObject("import QtQuick 2.2; import QtQuick.Dialogs 1.3;"
                                            + "MessageDialog {property alias msgDlg : msgDlg; id: msgDlg; text: \"400\"; height: 800; onAccepted : {} Component.onCompleted: visible = false}", root)
            msgDlg.msgDlg.text = msg
            msgDlg.msgDlg.icon = StandardIcon.Warning
            msgDlg.msgDlg.visible = true
            console.log("onSig_message " + msg)
        }
    }

    //荧光
    Connections {
        target: mInterface
        onSig_afpsUpdateChart : {
            for(var i = 0; i < 4; i++){
                mInterface.afpsUpdateChannelChart(i, afps.getChart(i).updateSeries(0), afps.getChart(i).getXAxis())
                afps.getChart(i).setYBkRange(mInterface.afpsGetDataRange(i)[0], mInterface.afpsGetDataRange(i)[1])
                afps.getChart(i).adjustAxisY(0)
            }
        }
    }
    Connections {
        target: afps
        onSig_start : {
            console.log("afps start " + para)
            mInterface.afpsStart(para)
        }
        onSig_stop : {
            mInterface.afpsStop()
        }        
        onSig_loadFile: {
            mInterface.afpsLoadFile(path)
        }
    }

    Component.onCompleted: {
        home.setInterface(mInterface)
        home.receiveAera.setModel(RawLog)
        //荧光默认数据文件目录
        var afpsDataPath = "file:///" + mInterface.curPath + "/Data"
        afps.setPath(afpsDataPath)
    }
}
