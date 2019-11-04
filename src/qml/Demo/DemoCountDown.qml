import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Item {
    id: cntDownRoot
    width: 800
    height: 800

    property var outerRadius: Math.min(width, height) / 2.0
    property var progressWidth: 40
    property var innerRadius: outerRadius - progressWidth - 10
    property var iColor: "#002EB7"
    property var detectColor: "red"
    property var from: 0
    property var value: 10
    property var to: 10
    state: "Normal"

    //外圈
    Rectangle {
        id: outerCir
        anchors.centerIn: parent
        width:  outerRadius * 2
        height: width
        radius: width * 0.5
        antialiasing: true
        color: "white"
        border {
            color: iColor
            width: 1
        }
    }
    //内圈
    Rectangle {
        id: innerCir
        anchors.centerIn: parent
        width: innerRadius * 2
        height: width
        radius: width * 0.5
        antialiasing: true
        color: "white"
        border {
            color: iColor
            width: 1
        }
    }
    //进度指示
    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: outerRadius * 2
        height: width
        onPaint: {
            var centreX = canvas.width / 2.0;
            var centreY = canvas.height / 2.0;
            var ctx = canvas.getContext('2d');
            ctx.strokeStyle =  cntDownRoot.state === "Normal" ? iColor : detectColor;
            ctx.lineWidth = progressWidth;
            ctx.lineCap = "round"
            ctx.beginPath();
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            ctx.arc(centreX, centreY, (outerRadius+innerRadius)/2.0, -Math.PI/2.0, calcAngle(value), false);
            ctx.stroke();
        }
    }

    //检出时间文字
    Text {
        id: checkTimeLbl
        anchors.centerIn: parent
        bottomPadding: -20
        color: iColor
        font.pixelSize: 180
        text: value.toFixed(0)
        verticalAlignment: Text.AlignBottom
    }
    //检出物质文字
    Text {
        id: detectedLbl
        anchors.centerIn: parent
        bottomPadding: -20
        color: detectColor
        font.pixelSize: 200
        text: qsTr("可疑物")
        verticalAlignment: Text.AlignBottom
    }
    //时间单位
    DemoLabel {
        id: timeUnitLbl
        anchors {
            left: checkTimeLbl.right
            bottom: checkTimeLbl.bottom
        }
        color: iColor
        font.pixelSize: 40
        text: qsTr("s")
        verticalAlignment: Text.AlignBottom
    }
    //检出时间说明
    DemoLabel {
        id: timeDescribeLbl
        anchors {
            top: checkTimeLbl.bottom
            horizontalCenter: checkTimeLbl.horizontalCenter
        }
        color: iColor
        font.pixelSize: 20
        text: qsTr("检出时间")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignBottom
    }

    onValueChanged: {
        canvas.requestPaint()
    }

    function calcAngle(data) {
        var ret = (data * 1.0 / to) * 2 * Math.PI
        ret -= Math.PI / 2
        console.log("calc angle " + data + " " + to + " " + ret)
        return ret
    }

    states: [
        State {
            name: "Normal"
            PropertyChanges {
                target: outerCir
                border.color: iColor
            }
            PropertyChanges {
                target: innerCir
                border.color: iColor
            }
            PropertyChanges {
                target: checkTimeLbl
                visible: true
            }
            PropertyChanges {
                target: timeUnitLbl
                visible: true
            }
            PropertyChanges {
                target: timeDescribeLbl
                visible: true
            }
            PropertyChanges {
                target: detectedLbl
                visible: false
            }
        },
        State {
            name: "Detected"
            PropertyChanges {
                target: outerCir
                border.color: detectColor
            }
            PropertyChanges {
                target: innerCir
                border.color: detectColor
            }
            PropertyChanges {
                target: checkTimeLbl
                visible: false
            }
            PropertyChanges {
                target: timeUnitLbl
                visible: false
            }
            PropertyChanges {
                target: timeDescribeLbl
                visible: false
            }
            PropertyChanges {
                target: detectedLbl
                visible: true
            }
        }
    ]
}
