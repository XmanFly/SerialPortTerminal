import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0

/* 控制面板 */
GroupBox {
    property alias refreshRbtn: refreshRbtn
    property alias switchRbtn: switchRbtn
    property alias portNum: portNum
    property bool devState: false //设备 默认关闭

    signal refreshDev() //刷新设备
    signal switchDev(SerialPortPara para) //开关设备

    id: root
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
                enabled: !devState
            }
        }
        //波特率
        SettingItem {
            id: baudrate
            settingName {
                text: qsTr("波特率")
            }
            settingValue {
                enabled: !devState
                model: [9600, 115200]
            }
            Component.onCompleted: {
                settingValue.currentIndex = 1
            }
        }
        //位数
        SettingItem {
            id: dataBit
            settingName {
                text: qsTr("数据位数")
            }
            settingValue {
                enabled: !devState
                model: [5, 6, 7, 8]
                currentIndex: 3
            }
        }
        //停止位
        SettingItem {
            id: stopBit
            settingName {
                text: qsTr("停止位")
            }
            settingValue {
                enabled: !devState
                model: [1, 1.5, 2]
            }
        }
        //校验位
        SettingItem {
            id: check
            settingName {
                text: qsTr("校验位")
            }
            settingValue {
                enabled: !devState
                model: ["None", "Odd", "Even", "Mark", "Space"]
            }
        }
        //流控制
        SettingItem {
            id: flowControl
            settingName {
                text: qsTr("流控制")
            }
            settingValue {
                enabled: !devState
                model: ["None", "Hardware", "Software"]
            }
        }
        MenuSeparator {
            Layout.fillWidth:  true
        }
        RowLayout {
            Layout.fillWidth: true
            spacing: 20
            RoundButton {
                id: refreshRbtn
                implicitWidth: 100
                radius: 2
                text: qsTr("刷新")
                enabled: !devState
                onClicked: {
                    refreshDev();
                    console.log("refreshDev clicked")
                }
            }
            RoundButton {
                id: switchRbtn
                radius: 2
                implicitWidth: 100
                text: {
                    if(devState === false) {
                        return qsTr("开启")
                    } else {
                        return qsTr("关闭")
                    }
                }
                onClicked: {
                    switchDev(getSerialPortPara());
                    console.log("switchDev clicked")
                }
            }
        }
    }

    //设置端口号
    function setPortName(nameList){
        portNum.valueListModel.clear()
        for (var id in nameList){
            console.log("setPortName " , id, nameList[id]
                        , typeof(nameList), typeof(nameList[id]))
            portNum.valueListModel.append({value: nameList[id]})
        }
        portNum.settingValue.currentIndex = 0 //选中第一项
    }
    //获取串口参数
    function getSerialPortPara(){
        //创建串口参数对象
        var mPara = Qt.createQmlObject("import QtQuick 2.9; import SerialPortTerminal.SerialPortPara 1.0;"
                                       + "SerialPortPara {}", root)
        mPara.number = portNum.getSettingValue()
        mPara.baudrate = baudrate.getSettingValue()
        mPara.databit = dataBit.getSettingValue()
        mPara.stopbit = stopBit.getSettingValue()
        return mPara
    }
    //获取开关状态
    function getSwitchState(){
        var state
        if(switchRbtn.text === "开启"){
            state = true
        } else {
            state = false
        }
        return state
    }
    //设置开关状态
    function setSwitchState(isOpen){
        if(isOpen){
            switchRbtn.text = "关闭"
        } else {
            switchRbtn.text = "开启"
        }
    }
}

