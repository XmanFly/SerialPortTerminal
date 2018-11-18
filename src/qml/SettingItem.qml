import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3


/* 单个设置选项 */
Rectangle {
    height: 30
    Layout.fillWidth: true

    property alias settingName: settingName
    property alias settingValue: settingValue
    property alias valueListModel: valueListModel

    RowLayout {
        anchors {
            fill: parent
        }
        //名称
        Text {
            id: settingName
        }
        //值
        ComboBox {
            id: settingValue
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            model: ListModel {
                    id: valueListModel
//                    ListElement { value: 123 }
                }
        }
    }
    function getSettingValue(){
        return settingValue.currentText
    }
}
