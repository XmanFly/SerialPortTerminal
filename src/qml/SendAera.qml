import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import SerialPortTerminal.SerialPortPara 1.0

/* 发送区域 */
GroupBox {
    id: root
    title: qsTr("发送区")
    contentHeight: 100 //指定内容高度 防止循环绑定
    implicitWidth: 100 //指定宽度 防止循环绑定

    property bool sendEnable: false //发送使能

    signal sendData(string data) //发送数据
    signal periodSend(int period, string data ,bool isEnable) //自动发送使能

    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 10

        ScrollView {
            id: view
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 8 / 10
            TextArea {
                id: sendBuffer
                placeholderText: qsTr("输入发送字符")
                color: "blue"
                font {
                    pointSize: 12
                }
                selectByMouse: true
                background :
                    Rectangle {
                        anchors.fill: parent
//                        color: "lightgray"
                    }
            }
        }

        RowLayout {
            Layout.preferredWidth: parent.width
            RowLayout {
                //清空按钮
                RoundButton {
                    id: clearRbtn
                    implicitWidth: 100
                    radius: 2
                    text: qsTr("清空")
                    onClicked: {
                        sendBuffer.clear()
                    }
                }
                ToolSeparator {}
                FormatSwitch {
                    id: formatRect
                }
                ToolSeparator {}
                //定时发送
                TextArea {
                    id: sendPeriod
                    width: 100
                    placeholderText: qsTr("输入间隔(ms)")
                    enabled: sendEnable
                }
                Switch {
                    id: periodSendSw
                    text: qsTr("定时发送")
                    enabled: sendEnable
                    checked: setCheckedState()

                    //禁用发送定时器
                    Timer {
                        id: disableSendTimer;
                        interval: 10;
                        running: false;
                        repeat: false;
                        triggeredOnStart: false;
                        onTriggered:{
                            periodSendSw.checked = false
                            //恢复绑定
                            periodSendSw.checked = Qt.binding(function(){return periodSendSw.setCheckedState()})
                        }
                    }

                    function setCheckedState(){
                        if(sendEnable){
                            console.log("send switch checked hold " + checked)
                            return checked
                        } else {
                            console.log("send switch checked " + false)
                            return false
                        }
                    }

                    onCheckedChanged: {
                        if(sendPeriod.text === "" || sendBuffer.text === ""){
                            console.log("period send Changed invalid value")
                            return
                        }
                        periodSend(sendPeriod.text*1, sendBuffer.text, checked)
                        console.log("period send Changed " + checked)
                    }
                    onClicked: {
                        if(sendPeriod.text === "") {
                            warnMsg(qsTr("周期不能为空!"))
                            disableSendTimer.start()
                            return
                        }
                        if(sendBuffer.text === ""){
                            warnMsg(qsTr("发送内容不能为空!"))
                            disableSendTimer.start()
                            return
                        }
                    }
                }
                ToolSeparator {}
            }
            //发送按钮
            RoundButton {
                id: sendRbtn
                implicitWidth: 100
                radius: 2
                text: qsTr("发送")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                enabled: sendEnable
                onClicked: {
                    sendData(sendBuffer.text)
                }
            }
        }
    }

    function warnMsg(hint) {
        //创建消息弹窗
        var msgDlg = Qt.createQmlObject("import QtQuick 2.9; import QtQuick.Dialogs 1.1;"
                                        + "MessageDialog {property alias msgDlg : msgDlg; id: msgDlg; onAccepted : {} Component.onCompleted: visible = true}", root)
        msgDlg.msgDlg.text = hint
        msgDlg.msgDlg.icon = StandardIcon.Warning
        return msgDlg
    }
    //设置发送格式model
    function setFormatModel(mModel){
        formatRect.fomatRpt.model = mModel
    }
}
