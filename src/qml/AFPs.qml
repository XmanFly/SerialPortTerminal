import QtQuick 2.4

AFPsForm {
    signal sig_start()
    signal sig_stop()

    switchBtn {
        onClicked: {
            if(switchBtn.text === "开始") {
                switchBtn.text = "停止"
                sig_start()
            } else {
                switchBtn.text = "开始"
                sig_stop()
            }
        }
    }

    function getChart(id){
        return chartRpt.itemAt(id)
    }

}
