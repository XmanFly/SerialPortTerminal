import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Item {
    width: 1920
    height: 1080

    DemoHeader {
        id: header
        anchors {
            top: parent.top
        }
        width: parent.width
        userName {
            text: qsTr("刘伟")
        }
    }

    ColumnLayout {
        anchors {
            top: header.bottom
            bottom: simFunc.top
            topMargin: 20
            bottomMargin: 20
        }
        width: parent.width
        spacing: 40
        DemoStatusBar {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.preferredHeight: 60
            Layout.fillWidth: true
        }
        DemoCountDown {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        DemoCheckBtn {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            Layout.preferredWidth: parent.width * 0.6
            Layout.preferredHeight: 60
            txt: qsTr("开始检测")
            visible: true
        }
    }
    Image {
        id: simFunc
        anchors {
            bottom: parent.bottom
        }
        width: parent.width
        source: "qrc:/src/image/simfunc.png"
    }
}
