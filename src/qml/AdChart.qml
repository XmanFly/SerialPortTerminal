import QtQuick 2.9
import QtQuick.Controls 2.2
import QtCharts 2.3

ChartView {
    id: chartView
    width: 400
    height: 200
    theme: ChartView.ChartThemeBlueIcy
    legend.visible: false   //关闭图例
    antialiasing: true //抗锯齿
    margins {
        top: 5
        bottom: 5
        left: 5
        right: 5
    }

    property bool cfgEnable : false
    property var model

    property int xScaleZoom: 0
    property int yScaleZoom: 0
    property var curPressBtn //当前单击按钮

    //缩放矩形
    Rectangle{
        id: recZoom
        border.color: "steelblue"
        border.width: 1
        color: "steelblue"
        opacity: 0.3
        visible: false
        transform: Scale { origin.x: 0; origin.y: 0; xScale: xScaleZoom; yScale: yScaleZoom}
    }

    //坐标文本
    Text {
        id: posTxt
        color: "red"
        function setPos(x, y, mapX, mapY){
            posTxt.x = x
            posTxt.y = y - 20
            posTxt.text = mapX.toFixed(2) + ", " + mapY.toFixed(3)
        }
    }

    //谱图自定义缩放
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MidButton
        property var curPressBtn //当前单击按钮
        z: 7
        onPressed: {
            switch(mouse.button){
                case Qt.LeftButton:
                    recZoom.x = mouseX;
                    recZoom.y = mouseY;
                    recZoom.visible = true;
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
            }
        }
        onReleased: {
            switch(curPressBtn){
            case Qt.LeftButton:
                var x = (mouseX >= recZoom.x) ? recZoom.x : mouseX
                var y = (mouseY >= recZoom.y) ? recZoom.y : mouseY
                if (mouse.button === Qt.LeftButton){
                    chartView.zoomIn(Qt.rect(x, y, recZoom.width, recZoom.height));
                }
                recZoom.visible = false;
                break;
            }
            curPressBtn = Qt.NoButton
        }
        onDoubleClicked: {
            if (mouse.button === Qt.RightButton){
                chartView.zoomReset()
                axisFix()
            }
        }
        onPositionChanged: {
            var pos = chartView.mapToValue(Qt.point(mouse.x, mouse.y), chartView.series(0))
            posTxt.setPos(mouse.x, mouse.y, pos.x, pos.y)
            posTxt.visible = true
        }
        onExited: {
            posTxt.visible = false
        }
    }

    ValueAxis {
        id: axisX
        gridVisible : true
        min: 0
        max: 1000
    }

    ValueAxis {
        id: axisY
        gridVisible : true
        min: -1
        max: 2
    }

    property var axisXRange: [0, 2000] //保存XY轴谱图数据实际区间
    property var axisYRange: [0, 2]
    property int mode: 0 //切换显示模式 0 折线图 1柱状图

    /********************** 折线图 **************************/
    property var lineSeries //折线

    function createLine(){
        var series = chartView.createSeries(ChartView.SeriesTypeLine, "line",
                                             axisX, axisY);
        series.useOpenGL = true
        if(mode == 1){
            series.visible = false;
        }
        console.log("chart createLine")
        return series
    }
    function updateSeries(){
        if(typeof(lineSeries) == "undefined" || !lineSeries){
            lineSeries = createLine()
        }
        console.log("sample data updateSeries " + axisX.min + " " + axisX.max)
        return lineSeries
    }
    function isSeriesExist() {
        if(typeof(lineSeries) == "undefined" || !lineSeries){
            return false;
        } else {
            return true;
        }
    }
    //调整Y轴范围 将数据显示置于合适区间
    function adjustYAxis(){
        if(typeof(lineSeries) == "undefined" || !lineSeries){
            return
        }
        var max = axisYRange[1] //当前数据最大值
        var min = axisYRange[0] //当前数据最小值
        //最高点与最低点是否占据大部分空间
        var axisHeight = axisY.max - axisY.min
        var lineHeight = max - min
        console.log("min " + min + " max " + max +
                    " axisHeight " + axisHeight + " lineHeight " + lineHeight +
                    " axisYmin " + axisY.min + " axisYmax " + axisY.max);
        if(max<axisY.max && min>axisY.min && lineHeight/axisHeight>0.8){
            return //正常 退出
        } else {
            axisY.max = max + lineHeight * 0.2 + 0.01
            axisY.min = min - lineHeight * 0.2 - 0.01
        }

    }

    //调整X轴范围 将数据显示置于合适区间
    function adjustXAxis(){
        if(typeof(lineSeries) == "undefined" || !lineSeries){
            return
        }
        axisX.min = axisXRange[0]
        axisX.max = axisXRange[1]
        console.log("adjust x axis " + axisXRange[0] + " "+ axisXRange[1])
    }

    //获取X轴对象
    function getXAxis(){
        return axisX;
    }
    //获取Y轴对象
    function getYAxis(){
        return axisY;
    }
    //清空
    function clear(){
        chartView.removeAllSeries();
        clearLabel() //清空之前所有标签
    }
    //设置折线图可见性
    function setLineVisible(isVisible){
        if(isSeriesExist()){
            lineSeries.visible = isVisible;
        }
    }
    //设置XY轴实际区间
    function setAxisRange(xMin, xMax, yMin, yMax){
        axisXRange[0] = xMin
        axisXRange[1] = xMax
        axisYRange[0] = yMin
        axisYRange[1] = yMax
    }
    //谱图自适应
    function axisFix(){
        adjustXAxis()
        adjustYAxis()
    }
    //设置model
    function setModel(mModel){
        model = mModel
        mModel.sig_updateChart.connect(updateChart)
        //如果有峰位置信息 则连接此信号进行峰显示
        if(typeof(mModel.sig_peakList) != "undefined"){
            mModel.sig_peakList.connect(addPeakList)
        }
    }
    function updateChart(){
        console.log("chart update")
        model.updateChart(updateSeries(), getXAxis(), getYAxis())
        setAxisRange(model.sampleAxisRange.xMin,
                                 model.sampleAxisRange.xMax,
                                 model.sampleAxisRange.yMin,
                                 model.sampleAxisRange.yMax
                                 )
        //校准X轴
        adjustXAxis()
        //校准Y轴
        adjustYAxis()
    }
    /******************************************************/


    /********************** 峰信息图 **************************/
    property var mPeakInfor //储存本次所有峰值信息
    //添加峰信息
    function addPeakList(list){
        clearLabel() //清空之前所有标签
        mPeakInfor = list
        var lineSeries = chartView.series(0)
        if(typeof(lineSeries) == "undefined"){
            console.log("on addPeakInfor no line " )
            return
        }
        for(var i =0; i<list.peaks.length; i++){
            var pos = chartView.mapToPosition(list.peaks[i].pos, chartView.series(0))
            addLabel(pos, list.peaks[i].label)
        }
        console.log("on addPeakInfor success " + list.peaks.length )
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
    //刷新标签
    function refreshLabel(){
        if(typeof(mPeakInfor) == "undefined"){
            return
        }
        for(var i =0; i<mPeakInfor.peaks.length; i++){
            var pos = chartView.mapToPosition(mPeakInfor.peaks[i].pos, chartView.series(0))
            labelArray[i].label.x = pos.x
            labelArray[i].label.y = pos.y - labelArray[i].label.height - 3
        }
    }
    /******************************************************/

    Component.onCompleted: {
        createLine() //初始化创建一条线
    }
}

