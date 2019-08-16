#include "adchartvm.h"

AdChartVM::AdChartVM(QObject *parent) : QObject(parent)
{

}

//收到采样数据
void AdChartVM::slot_receiveData(QVector<QPointF> mData, AxisRange mAxisRange)
{
    qDebug() << TAG << "receive data" << mData.size();
    srcData = mData;
    sampleAxisRange = mAxisRange;
    emit sig_updateChart(); //发射更新谱图信号
}


//更新谱图
void AdChartVM::updateChart(QAbstractSeries *series, QAbstractAxis *xAxis, QAbstractAxis *yAxis)
{
    Q_UNUSED(xAxis)
    Q_UNUSED(yAxis)
    qDebug() << TAG << "para " ;
    if(series == nullptr){
        return;
    }
    //绘制当前谱图
    QLineSeries *xySeries = static_cast<QLineSeries *>(series);
    QPen pen = xySeries->pen();
    pen.setWidth(1);
    pen.setColor(QColor(0, 0, 0));
    xySeries->setUseOpenGL(true);
    xySeries->setPen(pen);
    xySeries->replace(srcData);    
}
