import QtQuick 2.4
import SerialPortTerminal.Interface 1.0

HomeForm {

    Interface {
        id: mInterface
    }

    ctrlPanel {
        onRefreshDevClicked: {
            var devList = mInterface.refreshDev()
            ctrlPanel.setPortName(devList)
//            console.log("kao", devList.size())
        }      
    }

}
