import QtQuick 2.4
import SerialPortTerminal.Interface 1.0

HomeForm {

    Interface {
        id: mInterface
    }

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
        }
    }

}
