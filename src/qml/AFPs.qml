import QtQuick 2.4
import SerialPortTerminal.AfpsCfgParaModule 1.0

AFPsForm {
    signal sig_start(var para)
    signal sig_stop()

    AfpsCfgParaModule {
        id: cfgPara
        fileName: "config.ini"
    }

    switchBtn {
        onClicked: {
            if(switchBtn.text === "开始") {
                switchBtn.text = "停止"
                var para = new Array();
                for(var i=0; i<3; i++){
                    para.push(cfgParaRpt.itemAt(i).)
                }
                sig_start(para)
            } else {
                switchBtn.text = "开始"
                sig_stop()
            }
        }
    }

    function getChart(id){
        return chartRpt.itemAt(id)
    }

    Component.onCompleted: {
        cfgPara.loadPara();
        cfgParaRpt.itemAt(0).model = cfgPara.numList;
        cfgParaRpt.itemAt(0).currentIndex = 0
        cfgParaRpt.itemAt(1).model = cfgPara.nameList;
        cfgParaRpt.itemAt(1).currentIndex = 0
        cfgParaRpt.itemAt(2).model = cfgPara.concentrationList;
        cfgParaRpt.itemAt(2).currentIndex = 0
    }
}
