﻿import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.12
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0
import "../qml/Demo"

ApplicationWindow {
    id: root
    visible: true
    width: 1920
    height: 1080
//    visibility : Window.FullScreen
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

        Demo {
            id: demo
        }

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
            text: qsTr("主页")
            background: Rectangle{
                color: tabBar.currentIndex === 0 ? "lightblue" : "gray"
            }
        }
        TabButton {
            implicitHeight: parent.height
            text: qsTr("端口")
            background: Rectangle{
                color: tabBar.currentIndex === 1 ? "lightblue" : "gray"
            }
        }
        TabButton {
            implicitHeight: parent.height
            text: qsTr("谱图")
            background: Rectangle{
                color: tabBar.currentIndex === 2 ? "lightblue" : "gray"
            }
        }
        TabButton {
            implicitHeight: parent.height
            text: qsTr("寄存器")
            background: Rectangle{
                color: tabBar.currentIndex === 3 ? "lightblue" : "gray"
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

    }
}
