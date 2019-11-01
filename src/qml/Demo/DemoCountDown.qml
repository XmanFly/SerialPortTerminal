import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12

Item {
    width: 800
    height: 800

    property var outerRadius: Math.min(width, height) / 2.0
//    property var outerRadius: 250
    property var progressWidth: 40
    property var innerRadius: outerRadius - progressWidth - 10
    property var iColor: "#002EB7"
    property var from: 0
    property var value: 1
    property var to: 10

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
            ctx.strokeStyle = iColor;
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
        text: value
        verticalAlignment: Text.AlignBottom
    }
    //时间单位
    DemoLabel {
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
}
