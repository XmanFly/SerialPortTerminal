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

    checkBtn {
        onClicked: {
            if(checkBtn.txt === qsTr("开始")) {
                checkBtn.txt = qsTr("停止")
                var para = new Array();
//                sig_start(para)
                mIf.afpsStart(para)
            } else {
                checkBtn.txt = "开始"
                mIf.afpsStop()
//                sig_stop()
            }
        }
    }

}
