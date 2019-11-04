import QtQuick 2.12

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
    }

}
