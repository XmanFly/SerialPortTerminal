#include "adchartmodel.h"

AdChartModel::AdChartModel(QObject *parent) :
    QObject(parent),
    isWork(false)
{
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channelRange.append(AxisRange());
    channelRange.append(AxisRange());
    channelRange.append(AxisRange());
    channelRange.append(AxisRange());
}

void AdChartModel::clear()
{
    //数据清空
    foreach(QVector<QPointF >* each, channel){
        each->clear();
    }
    //轴清空
    foreach(AxisRange each, channelRange){
        each.clear();
    }
}

void AdChartModel::slot_ctrl(bool isStart)
{
    if(isStart){
        isWork = true;
        clear();
        dataChanged();
    } else {
        isWork = false;
    }
}

void AdChartModel::slot_rcvData(AD_CHANNEDL_DATA data)
{
    if(!isWork){
        return;
    }
    channel[0]->append(QPointF((channel[0]->size() + 1) * 0.07, data.channel1));
    channel[1]->append(QPointF((channel[1]->size() + 1) * 0.07, data.channel2));
    channel[2]->append(QPointF((channel[2]->size() + 1) * 0.07, data.channel3));
    channel[3]->append(QPointF((channel[3]->size() + 1) * 0.07, data.channel4));
    calcRange();
    dataChanged();
    qDebug() << "AdChartModel thread id " << QThread::currentThreadId();
}

/* 计算每个通道数值范围 */
void AdChartModel::calcRange()
{
    for(int i=0; i<channel.size(); i++){
        double min = 1e10;
        double max = -1e10;
        foreach(QPointF eachPoint, *channel.at(i)) {
            min = eachPoint.y() < min ? eachPoint.y() : min;
            max = eachPoint.y() > max ? eachPoint.y() : max;
        }
        channelRange[i] = AxisRange(
                    channel.at(i)->first().x(),
                    channel.at(i)->last().x(),
                    min,
                    max
                    );
    }
}

void AdChartModel::dataChanged()
{
    emit sig_ch1Data(*channel[0], channelRange[0]);
    emit sig_ch2Data(*channel[1], channelRange[1]);
    emit sig_ch3Data(*channel[2], channelRange[2]);
    emit sig_ch4Data(*channel[3], channelRange[3]);
}

//收到单次采样所有数据
void AdChartModel::slot_rcvAllData(QVector<QVector<QPointF> > data)
{
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            channel[i]->append(data[i][j]);
        }
    }
    calcRange();
    dataChanged();
}
