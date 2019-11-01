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
    }

    Rectangle {
        anchors {
            top: header.bottom
            bottom: simFunc.top
            topMargin: 20
            bottomMargin: 20
        }
        width: parent.width
        DemoStatusBar {
            anchors {
                top: parent.top
            }
            width: parent.width
            height: 60
        }
        DemoCheckBtn {
            anchors {
                bottom: parent.bottom
                horizontalCenter: parent.horizontalCenter
            }
            width: parent.width * 0.6
            height: 60
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
