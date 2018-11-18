import QtQuick 2.9
import QtQuick.Controls 2.2
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0

ApplicationWindow {
    visible: true
    width: 1366
    height: 768
    title: qsTr("Tabs")

    Interface {
        id: mInterface
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Home {
            id: home

        }

        Page2Form {
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Page 1")
        }
        TabButton {
            text: qsTr("Page 2")
        }
    }

    Component.onCompleted: {
        home.setInterface(mInterface)
    }
}
