import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    width: 1366
    height: 768

    ReceiveAera {
        anchors.fill: parent
    }

    //    SendAera {
    //        anchors.fill: parent
    //    }

    //    ControlPanel {
    //        anchors {
    //            left: parent.left
    //            top: parent.top
    //        }
    //        width: parent.width * 2 / 10
    //    }

    //            SettingItem {
    //                anchors {
    //                        fill: parent
    //                }
    //                settingName {
    //                    text: qsTr("串口号")
    //                }
    //                settingValue {
    //                }
    //            }

    //    Rectangle {
    //    property alias settingName: settingName
    //    property alias settingValue: settingValue

    //                    anchors {
    //                    fill: parent
    //            }
    //                    color: "red"
    //RowLayout {
    ////    property alias settingName: settingName
    ////    property alias settingValue: settingValue
    //    anchors {
    //    fill: parent
    //}

    //    //名称
    //    Text {
    //        id: settingName
    //    }
    //    //值
    //    ComboBox {
    //        id: settingValue
    //        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
    //    }
    //}
    //}

    //    header: Label {
    //        text: qsTr("Page 1")
    //        font.pixelSize: Qt.application.font.pixelSize * 2
    //        padding: 10
    //    }

    //    Label {
    //        text: qsTr("You are on Page 1.")
    //        anchors.centerIn: parent
    //    }
}
