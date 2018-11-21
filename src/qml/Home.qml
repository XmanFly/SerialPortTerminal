import QtQuick 2.4
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0

HomeForm {

    property Interface mInterface

    //设置面板
    ctrlPanel {
        //刷新设备
        onRefreshDev: {
            refreshDev()
        }      
        //打开设备
        onSwitchDev: {
            console.log("switch port",
                        para.number, para.baudrate, para.databit, para.stopbit)
            var curState = ctrlPanel.getSwitchState();
            if(curState){
                mInterface.setSerialPortPara(para)
            }
            mInterface.switchDev(curState)
        }
    }

    //数据个数统计区
    dataInforPanel {
        onClearCnt: {
            mInterface.clearCnt(id)
        }
    }

    //发送区域
    sendAera {
        //发送数据
        onSendData: {
            mInterface.sendData(data)
        }
        //定时发送
        onPeriodSend: {
            mInterface.periodSendStart(period, data, isEnable)
        }
    }

    function setInterface(mInf){
        mInterface = mInf
        receiveAera.setModel(mInf.getDataModel())
        dataInforPanel.setDataModel(mInf.getDataCntModel())
    }

    //刷新设备名
    function refreshDev(){
        var devList = mInterface.refreshDev()
        ctrlPanel.setPortName(devList)
    }

    Binding {
        target: ctrlPanel
        property: "devState"
        value: mInterface.serialState
    }

    Binding {
        target: sendAera
        property: "sendEnable"
        value: mInterface.serialState
    }

    Connections {
        target: mInterface
        onSig_resetDataList : {
            receiveAera.setModel(mInterface.getDataModel())
        }
    }

    Component.onCompleted: {
        refreshDev()
    }
}
