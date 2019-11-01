import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Item {
    width: 1920
    height: 60

    property alias time: time
    property alias sysState: sysState
    property alias exception: exception
    property alias shutdownBtn: shutdownBtn
    property alias userRole: userRole
    property alias userName: userName

    //背景
    Rectangle {
        anchors.fill: parent
        color: "#002A66"
    }
    //公司Logo
    Image {
        id: logo
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 10
        }
        height: 40
        source: "qrc:/src/image/logo.png"
    }
    //用户信息
    RowLayout {
        id: userInfor
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: logo.right
            leftMargin: 10
        }
        spacing: 20
        //头像
        Image {
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            source: "qrc:/src/image/face.gif"
        }
        DemoLabel {
            id: userRole
            text: qsTr("管理员")
        }
        DemoLabel {
            id: userName
            text: qsTr("")
        }
    }
    //错误信息
    RowLayout {
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: userInfor.right
            leftMargin: 10
        }
        DemoLabel {
            id: exception
            text: qsTr("")
            color: "red"
        }
    }
    //其他信息
    RowLayout {
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            rightMargin: 10
        }
        spacing: 20
        //设备名称
        DemoLabel {
            text: qsTr("荧光100 爆炸物检测仪")
        }
        //系统状态
        DemoLabel {
            id: sysState
            Layout.preferredWidth: 200
            text: qsTr("系统状态正常")
        }
        //时间
        DemoLabel {
            id: time
            text: qsTr("")
        }
        //wifi标志
        Image {
            Layout.preferredHeight: 30
            Layout.preferredWidth: 30
            source: "qrc:/src/image/wifi100.png"
        }
        //关机按钮
        Button {
            id: shutdownBtn
            Layout.preferredWidth: 50
            Layout.fillHeight: true
            text: qsTr("关机")
            contentItem: DemoLabel {
                text: shutdownBtn.text
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: "white"
            }
            background: Rectangle {
                color: "transparent"
            }
        }
    }
}
