﻿import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 1920
    height: 1080
    title: qsTr("苏州微木荧光调试软件")

    SwipeView {
        id: swipeView
        anchors {
            fill: parent
            topMargin: 20
        }
        currentIndex: tabBar.currentIndex
        interactive: false
        clip: true

        Home {
            id: home

        }
        AFPs {
            id: afps
        }
        RegisterList {
            id: afpsRegister
            name: qsTr("寄存器")
            regModel: RegModule.RWList.readWriteList
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
            text: qsTr("谱图")
            background: Rectangle{
                color: tabBar.currentIndex === 1 ? "lightblue" : "gray"
            }
        }
        TabButton {
            implicitHeight: parent.height
            text: qsTr("寄存器")
            background: Rectangle{
                color: tabBar.currentIndex === 2 ? "lightblue" : "gray"
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
        afps.getChart(0).setModel(AdChart1VM)
        afps.getChart(1).setModel(AdChart2VM)
        afps.getChart(2).setModel(AdChart3VM)
        afps.getChart(3).setModel(AdChart4VM)
        afps.getChart(4).setModel(FlowVM)
    }
}
