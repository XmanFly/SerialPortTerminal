import QtQuick 2.12
import Algorithm 1.0

DemoForm {
    id: demoRoot
    signal sig_start(var para)
    signal sig_stop()

    property var mIf
    property var mAlgorithm
    state: "Normal"

    header {
        shutdownBtn {
            onClicked: {
                Qt.quit()
            }
        }
    }

    statusBar {
        statusLbl {
            text: mAlgorithm.state
        }
    }

    cntDown {
        from: 0
        to: 15
        value: 15
    }

    Timer {
        id: cntDownTimer
        interval: 20
        running: false
        repeat: true
        onTriggered: {
            cntDown.value -= 0.02
            if(Math.abs(cntDown.value, 0) < 0.0001){
                cntDownTimer.stop()
                ctrl(false)
            }
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
            state = "Normal"
            cntDown.state = "Normal"
            cntDown.value = 15
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
//                ctrl(false)
                cntDown.state = "Timeout"
                cntDown.value = cntDown.value //触发进度条重绘 重新上色
                break
            case Algorithm.DETECTED:
                ctrl(false)
                demoRoot.state = "Detected"
                cntDown.state = "Detected"
                cntDown.value = cntDown.value //触发进度条重绘 重新上色
                break
            }
        }
    }

    states: [
        State {
            name: "Normal"
            PropertyChanges {
                target: statusBar.statusLbl
                color: "white"
            }
        },
        State {
            name: "Detected"
            PropertyChanges {
                target: statusBar.statusLbl
                color: "red"
            }
        }
    ]

}
