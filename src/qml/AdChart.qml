import QtQuick 2.0

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.2

//![1]
ChartView {
    id: chartView
    backgroundRoundness: 3
    theme: ChartView.ChartThemeLight
    legend.visible: false   //关闭图例
    antialiasing: true //抗锯齿
    Component.onCompleted: {

    }

    property int xmin : 0
    property int xmax : 67500
    property int ymin : 0
    property int ymax : 2
    property bool peakVisible: false //峰值标签使能
    property bool translationEnable: false //拖动使能
    property bool updateXEnable: true //X轴范围变更使能

    ValueAxis {
        id: axisY
        gridVisible : true
        min: ymin
        max: ymax
    }

    ValueAxis {
        id: axisX
        gridVisible : true
        min: ymin
        max: ymax
    }

    property int xScaleZoom: 0
    property int yScaleZoom: 0

    Rectangle{
        id: recZoom
        border.color: "steelblue"
        border.width: 1
        color: "steelblue"
        opacity: 0.3
        visible: false
        transform: Scale { origin.x: 0; origin.y: 0; xScale: xScaleZoom; yScale: yScaleZoom}
    }
    property var axisXBk: [0, 2000]
    property var axisYBk: [0, 2]
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MidButton
        property var translationBeginAxisX: [0, 0] //平移开始前X坐标轴
        property var translationBeginAxisY: [0, 0] //平移开始前Y坐标轴
        property var translationBeginPos: [0, 0] //平移开始前坐标
        property var translationScale: [1, 1] //平移缩放因子 校准坐标轴与像素尺寸
        property var curPressBtn //当前单击按钮
        onPressed: {
            switch(mouse.button){
            case Qt.LeftButton:
                recZoom.x = mouseX;
                recZoom.y = mouseY;
                recZoom.visible = true;
                break;
            case Qt.MidButton:
                if(translationEnable) {
                    translationBeginPos[0] = mouseX;
                    translationBeginPos[1] = mouseY;
                    translationBeginAxisX[0] = axisX.min
                    translationBeginAxisX[1] = axisX.max
                    translationBeginAxisY[0] = axisY.min
                    translationBeginAxisY[1] = axisY.max
                    //确定平移因子
                    var pos1 = chartView.mapToPosition(Qt.point(0, 0), chartView.series(0))
                    var pos2 = chartView.mapToPosition(Qt.point(axisX.max, axisY.max), chartView.series(0))
                    translationScale[0] = (pos2.x - pos1.x) / axisX.max;
                    translationScale[1] = (pos2.y - pos1.y) / axisY.max;
                    translationScale[0] = translationScale[0]===0 ? 1 : translationScale[0];
                    translationScale[1] = translationScale[1]===0 ? 1 : translationScale[1];
                    //确定更新x轴使能 开始检测并收到数据
                    if(isSeriesExist()){
                        updateXEnable = false
                    }
                }
                break;
            }
            curPressBtn = mouse.button
        }
        onMouseXChanged: {
            switch(curPressBtn){
            case Qt.LeftButton:
                if (mouseX - recZoom.x >= 0) {
                    xScaleZoom = 1;
                    recZoom.width = mouseX - recZoom.x;
                } else {
                    xScaleZoom = -1;
                    recZoom.width = recZoom.x - mouseX;
                }
                break;
            case Qt.MidButton:
                if(translationEnable) {
                    var xMinTmp = translationBeginAxisX[0] - (mouseX-translationBeginPos[0]) / translationScale[0]
                    var xMaxTmp = translationBeginAxisX[1] - (mouseX-translationBeginPos[0]) / translationScale[0]
                    axisX.min = xMinTmp;
                    axisX.max = xMaxTmp;
                    refreshLabel();
                }
                break;
            }
        }
        onMouseYChanged: {
            switch(curPressBtn){
            case Qt.LeftButton:
                if (mouseY - recZoom.y >= 0) {
                    yScaleZoom = 1;
                    recZoom.height = mouseY - recZoom.y;
                } else {
                    yScaleZoom = -1;
                    recZoom.height = recZoom.y - mouseY;
                }
                break;
            case Qt.MidButton:
                if(translationEnable) {
                    var yMinTmp = translationBeginAxisY[0] - (mouseY-translationBeginPos[1]) / translationScale[1]
                    var yMaxTmp = translationBeginAxisY[1] - (mouseY-translationBeginPos[1]) / translationScale[1]
                    axisY.min = yMinTmp;
                    axisY.max = yMaxTmp;
                    refreshLabel();
                }
                break;
            }

        }
        onReleased: {
            switch(curPressBtn){
            case Qt.LeftButton:
                var x = (mouseX >= recZoom.x) ? recZoom.x : mouseX
                var y = (mouseY >= recZoom.y) ? recZoom.y : mouseY
                if (mouse.button === Qt.LeftButton){
                    chartView.zoomIn(Qt.rect(x, y, recZoom.width, recZoom.height));
                    if(peakVisible) {
                        refreshLabel()
                    }
                }
                recZoom.visible = false;
                //确定更新x轴使能 开始检测并收到数据
                if(isSeriesExist()){
                    updateXEnable = false
                }
                break;
            case Qt.MidButton:

                break;
            }
            curPressBtn = Qt.NoButton
        }
        onDoubleClicked: {
            if (mouse.button === Qt.RightButton){
                chartView.zoomReset()
                if(peakVisible) {
                    axisRestore();
                    adjustAxisY(0);
                    refreshLabel();
                }
            }
        }
    }
    Button {
        anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }
        text: "test"
        visible: false
        onClicked: {
            if(peakVisible) {
                refreshLabel()
            }
            console.log("refresh label clicked")
        }
    }

//![1]
    function createLine(){
        //重置轴范围
        axisX.min = xmin;
        axisX.max = xmax;
//        axisY.min = ymin;
//        axisY.max = ymax;
        var series = chartView.createSeries(ChartView.SeriesTypeLine, "nani",
                                             axisX, axisY);
        series.useOpenGL = true
        return series
    }
    function updateSeries(id){
        var series = chartView.series(id)
        if(typeof(series) == "undefined" || !series){
            series = createLine()
        }
        return series
    }
    function isSeriesExist() {
        var series = chartView.series(0)
        if(typeof(series) == "undefined" || !series){
            return false;
        } else {
            return true;
        }
    }
    //调整Y轴范围 将数据显示置于合适区间
    function adjustAxisY(id){
        var lineSeries = chartView.series(id)
        if(typeof(lineSeries) == "undefined"){
            return
        }
        var max = axisYBk[1] //当前数据最大值
        var min = axisYBk[0] //当前数据最小值
        //最高点与最低点是否占据大部分空间
        var axisHeight = axisY.max - axisY.min
        var lineHeight = max - min
        if(max<axisY.max && min>axisY.min && lineHeight/axisHeight>0.8){
            return //正常 退出
        } else {
            axisY.max = max + lineHeight * 0.2 + 0.001
            axisY.min = min - lineHeight * 0.2 - 0.001
        }
//        console.log("min " + min + " max " + max);
    }
    //调整Y轴范围 将数据显示置于合适区间 检索当前图形数据
    function adjustAxisYFromChart(id){
        var lineSeries = chartView.series(id)
        if(typeof(lineSeries) == "undefined"){
            return
        }
        var max = -1e10//当前数据最大值
        var min = 1e10 //当前数据最小值
        for(var i = 0; i < lineSeries.count; ++i){
            if(lineSeries.at(i).y > max){
                max = lineSeries.at(i).y;
            }
            if(lineSeries.at(i).y < min){
                min = lineSeries.at(i).y;
            }
        }
        //最高点与最低点是否占据大部分空间
        var axisHeight = axisY.max - axisY.min
        var lineHeight = max - min
        if(max<axisY.max && min>axisY.min && lineHeight/axisHeight>0.8){
            return //正常 退出
        } else {
            axisY.max = max + lineHeight * 0.2 + 0.001
            axisY.min = min - lineHeight * 0.2 - 0.001
        }
//        console.log("min " + min + " max " + max);
    }
    //获取X轴对象
    function getXAxis(){
        return axisX;
    }
    //获取X轴最小值
    function getXMinBk(){
        return axisXBk[0];
    }
    function createAxis(min, max) {
        // The following creates a ValueAxis object that can be then set as a x or y axis for a series
        return Qt.createQmlObject("import QtQuick 2.9; import QtCharts 2.2; ValueAxis { min: "
                                  + min + "; max: " + max + " }", chartView);
    }
    function setAnimations(enabled) {
        if (enabled)
            chartView.animationOptions = ChartView.SeriesAnimations;
        else
            chartView.animationOptions = ChartView.NoAnimation;
    }
    function clear(){
        chartView.removeAllSeries();
        clearLabel() //清空之前所有标签
    }
    property var labelArray : [] //标签数组 存放动态创建的标签
    //添加一个新标签
    function addLabel(pos, txt){
        var msgDlg = Qt.createQmlObject("import QtQuick 2.9; "
                                        + "Item {property alias label: label; Text {id: label } }", chartView);
        msgDlg.label.text = txt
        msgDlg.label.x = pos.x
        msgDlg.label.y = pos.y - msgDlg.label.height - 3
        labelArray.push(msgDlg)
    }
    //清空之前所有标签
    function clearLabel(){
        var len = labelArray.length
        while(len--){
            labelArray[len].destroy(0)
            labelArray.pop()
        }
    }
    //备份当前坐标轴信息 用作复位时还原
    function axisBk(){
        axisXBk[0] = axisX.min;
        axisXBk[1] = axisX.max;
//        axisYBk[0] = axisY.min;
//        axisYBk[1] = axisY.max;
    }
    //还原坐标轴
    function axisRestore(){
        axisX.min = axisXBk[0];
        axisX.max = axisXBk[1];
//        axisY.min = axisYBk[0];
//        axisY.max = axisYBk[1];
    }
    //绘图初始化
    function init(){
        clear()
        updateXEnable = true
    }
    //设置X轴备份
    function setXBkRange(min, max){
        axisXBk[0] = min;
        axisXBk[1] = max;
    }
    //设置Y轴备份
    function setYBkRange(min, max){
        axisYBk[0] = min;
        axisYBk[1] = max;
    }
}

