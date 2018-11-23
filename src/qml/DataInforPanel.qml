import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import SerialPortTerminal.SerialPortPara 1.0
import SerialPortTerminal.DataCntModel 1.0

/* 数据信息面板 */
GroupBox {
    id: root

    title: qsTr("数据统计")
    ColumnLayout {
        anchors {
            fill: parent
        }
        spacing: 20
        Repeater {
            id: cntRpt
            CntItem {
                itemName: model.modelData.name
                cnt: model.modelData.cnt
                clear {
                    onClicked: {
                        model.modelData.cnt = 0
                    }
                }
            }
        }
    }

    function setDataModel(mModel){
        cntRpt.model = mModel
    }
}
