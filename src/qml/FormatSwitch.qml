import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

/* 格式切换 */
RowLayout {
    id: root
    property alias fomatRpt: fomatRpt

    ButtonGroup {
        id: buttonGroup
    }
    Repeater {
        id: fomatRpt
        delegate: RadioDelegate {
            id: rd
            text: model.modelData.name
            checked: index == 0
            ButtonGroup.group: buttonGroup
            Binding {
                target: model.modelData
                property: "isSelected"
                value: rd.checked
            }
        }
    }
}
