import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

/* 控制面板 */
GroupBox {
    property alias refreshRbtn: refreshRbtn
    property alias switchRbtn: switchRbtn
    property alias portNum: portNum

    signal refreshDevClicked() //刷新设备


    title: qsTr("串口设置")
    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 20

        //串口号
        SettingItem {
            id: portNum
            settingName {
                text: qsTr("串口号")
            }
            settingValue {
            }
        }
        //波特率
        SettingItem {
            settingName {
                text: qsTr("波特率")
            }
            settingValue {
                model: [9600, 115200]
            }
        }
        //位数
        SettingItem {
            settingName {
                text: qsTr("数据位数")
            }
            settingValue {
                model: [5, 6, 7, 8]
            }
        }
        //停止位
        SettingItem {
            settingName {
                text: qsTr("停止位")
            }
            settingValue {
                model: [1, 1.5, 2]
            }
        }
        //校验位
        SettingItem {
            settingName {
                text: qsTr("校验位")
            }
            settingValue {
                model: ["None", "Odd", "Even", "Mark", "Space"]
            }
        }
        //流控制
        SettingItem {
            settingName {
                text: qsTr("流控制")
            }
            settingValue {
                model: ["None", "Hardware", "Software"]
            }
        }
        RowLayout {
            Layout.fillWidth: true
            spacing: 20
            RoundButton {
                id: refreshRbtn
                implicitWidth: 100
                radius: 2
                text: qsTr("刷新")
                onClicked: {
                    refreshDevClicked();
                    console.log("refreshDev clicked")
                }
            }
            RoundButton {
                id: switchRbtn
                radius: 2
                implicitWidth: 100
                text: qsTr("开启")
            }
        }
    }

    function setPortName(nameList){
        portNum.valueListModel.clear()
        for (var id in nameList){
            console.log("setPortName " , id, nameList[id]
                        , typeof(nameList), typeof(nameList[id]))
            portNum.valueListModel.append({value: nameList[id]})
        }
        portNum.settingValue.currentIndex = 0 //选中第一项
    }
}

