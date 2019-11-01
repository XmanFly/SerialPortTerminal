import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3
import QtQuick.Window 2.12
import SerialPortTerminal.Interface 1.0
import SerialPortTerminal.SerialPortPara 1.0
import "../qml/Demo"

ApplicationWindow {
    id: root
    visible: true
    width: 1920
    height: 1080
    visibility : Window.FullScreen
    title: qsTr("苏州微木荧光调试软件")

    Demo {
        anchors.fill: parent
    }

}
