import QtQuick 2.4
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0

HomeForm {

    property Interface mInterface

    ctrlPanel {
        //刷新设备
        onRefreshDev: {
            var devList = mInterface.refreshDev()
            ctrlPanel.setPortName(devList)
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

    function setInterface(mInf){
        mInterface = mInf
    }

    Connections {
        target: mInterface
        onSig_serialPortState : {
            ctrlPanel.setSwitchState(isOpen)
        }
    }
}
