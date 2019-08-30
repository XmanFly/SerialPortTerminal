import QtQuick 2.9
import SerialPortTerminal.AfpsCfgParaModule 1.0

AFPsForm {
    signal sig_start(var para)
    signal sig_stop()
    signal sig_loadFile(var path)

    property alias cfgPara: cfgPara

    AfpsCfgParaModule {
        id: cfgPara
        fileName: "config.ini"
    }

    fileExp {
        onSig_loadFile: {
            sig_loadFile(path)
        }                
    }

    switchBtn {
        onClicked: {
            if(switchBtn.text === qsTr("开始")) {
                switchBtn.text = qsTr("停止")
                var para = new Array();
                for(var i=0; i<3; i++){
                    para.push(cfgParaRpt.itemAt(i).currentText)
                }
                para.push(userDefined.text)
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

    function setPath(path){
        fileExp.setCurPath(path)
    }

    Component.onCompleted: {
        cfgPara.loadPara();
        cfgParaRpt.itemAt(0).model = cfgPara.numList;
        cfgParaRpt.itemAt(0).currentIndex = 0
        cfgParaRpt.itemAt(1).model = cfgPara.nameList;
        cfgParaRpt.itemAt(1).currentIndex = 0
        cfgParaRpt.itemAt(2).model = cfgPara.concentrationList;
        cfgParaRpt.itemAt(2).currentIndex = 0
        paraMonitor.paraList.model = Monitor.list
        func.cleanBtn.onClicked.connect(function() { WashCtrl.u8W.writeSync(1) })

        //算法模块使能控制
        algorithm.visible = cfgPara.algorithmEn
        //谱图模块使能控制
        if(cfgPara.flowChartEn){
            getChart(4).setModel(FlowVM)
        } else {
            chartRpt.model = 4
        }
        getChart(0).setModel(AdChart1VM)
        getChart(1).setModel(AdChart2VM)
        getChart(2).setModel(AdChart3VM)
        getChart(3).setModel(AdChart4VM)
    }
}
