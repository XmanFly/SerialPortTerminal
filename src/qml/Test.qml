import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import RequestStyle 1.0

Page {
    width: 1366
    height: 768

    RegSetFloatItem {
        msgTxt  {
            text: Pump.dbgMsg
            color: getMsgColor(Pump.state)
        }
        setBtn {
            onClicked: {
                console.log("set float ")
                Pump.writeSync(parseFloat(input.text))
            }
        }
    }

    function getMsgColor(state){
        var color
        switch(state){
        case RequestStyle.READY :
        case RequestStyle.IN_PROCESS:
            color = "black"
            break;
        case RequestStyle.RESPONSED:
            color = "green"
            break;
        case RequestStyle.TIMEOUT:
        case RequestStyle.ERROR:
            color = "red"
            break;
        }
        return color
    }
}
