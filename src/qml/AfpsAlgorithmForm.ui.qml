import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

GroupBox {
    id: root
    width: 400
    height: 800
    title: qsTr("算法参数")

    /* 基线配置 */
    GroupBox {
        id: baselineCfg
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        //        height: parent.height * 1 / 5
        title: qsTr("基线配置")

        GridLayout {
            anchors.fill: parent
            columns: 2
            Text {
                Layout.preferredWidth: parent.width / 2
                text: qsTr("窗口")
            }
            TextInput {
                text: qsTr("51")
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: qsTr("稳定阈值")
            }
            TextInput {
                text: qsTr("700")
            }
        }
    }

    /* 识别配置 */
    GroupBox {
        id: identifyCfg
        anchors {
            left: parent.left
            right: parent.right
            top: baselineCfg.bottom
            topMargin: 20
        }
        //        height: parent.height * 1 / 5
        title: qsTr("识别配置")

        GridLayout {
            anchors.fill: parent
            columns: 2

            Text {
                Layout.preferredWidth: parent.width / 2
                text: qsTr("最大点数")
            }
            TextInput {
                text: qsTr("131")
            }
            Text {
                text: qsTr("报警阈值")
            }
            TextInput {
                text: qsTr("0.045")
            }
        }
    }

    /* 检测输出 */
    GroupBox {
        id: outputPara
        anchors {
            left: parent.left
            right: parent.right
            top: identifyCfg.bottom
            topMargin: 20
        }
        //        height: parent.height * 1 / 5
        title: qsTr("输出")

        GridLayout {
            anchors.fill: parent
            columns: 2

            Text {
                Layout.preferredWidth: parent.width / 2
                text: qsTr("状态")
            }
            Text {
                text: qsTr("")
            }
            Text {
                text: qsTr("检测结果")
            }
            Text {
                text: qsTr("")
            }
            Text {
                text: qsTr("基准值")
            }
            Text {
                text: qsTr("")
            }
            Text {
                text: qsTr("差值")
            }
            Text {
                text: qsTr("")
            }
            Text {
                text: qsTr("差值比例")
            }
            Text {
                text: qsTr("")
            }
        }
    }
}
