import QtQuick 2.12
import Algorithm 1.0

DemoForm {

    signal sig_start(var para)
    signal sig_stop()

    property var mIf
    property var mAlgorithm

    statusBar {
        statusLbl {
            text: mAlgorithm.state
        }
    }

    cntDown {
        from: 0
        to: 60
        value: 0
    }

    Timer {
        id: cntDownTimer
        interval: 1000
        running: false
        repeat: true
        onTriggered: {
            cntDown.value++
        }
    }

    checkBtn {
        onClicked: {
            if(checkBtn.txt === qsTr("开始")) {
                ctrl(true)
            } else {
                ctrl(false)
            }
        }
    }

    function ctrl(isOn){
        if(isOn){
            checkBtn.txt = qsTr("停止")
            var para = new Array();
//                sig_start(para)
            mIf.afpsStart(para)
            cntDown.value = 0
            cntDownTimer.running = true
        } else {
            checkBtn.txt = "开始"
            mIf.afpsStop()
//                sig_stop()
            cntDownTimer.running = false
        }
    }

    Connections {
        target: mAlgorithm
        onSig_stateEnumChanged : {
            switch(state){
            case Algorithm.TIMEOUT:
                ctrl(false)
            }
        }
    }

}
