#include "adchartmodel.h"

AdChartModel::AdChartModel(QObject *parent) :
    QObject(parent),
    isWork(false)
{
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    calcRange();
}

void AdChartModel::clear()
{
    foreach(QVector<QPointF >* each, channel){
        each->clear();
    }
}

void AdChartModel::slot_ctrl(bool isStart)
{
    if(isStart){
        isWork = true;
        clear();
        emit sig_dataUpdate();
    } else {
        isWork = false;
    }
}

void AdChartModel::slot_rcvData(AD_CHANNEDL_DATA data)
{
    if(!isWork){
        return;
    }
    channel[0]->append(QPointF(channel[0]->size() + 1, data.channel1));
    channel[1]->append(QPointF(channel[1]->size() + 1, data.channel2));
    channel[2]->append(QPointF(channel[2]->size() + 1, data.channel3));
    channel[3]->append(QPointF(channel[3]->size() + 1, data.channel4));
    calcRange();
    emit sig_dataUpdate();
}

/* 计算每个通道数值范围 */
void AdChartModel::calcRange()
{
    channelRange.clear();
    for(int i=0; i<channel.size(); i++){
        double min = 1e10;
        double max = -1e10;
        foreach(QPointF eachPoint, *channel.at(i)) {
            min = eachPoint.y() < min ? eachPoint.y() : min;
            max = eachPoint.y() > max ? eachPoint.y() : max;
        }
        QVector<double > range;
        range.append(min);
        range.append(max);
        channelRange.append(range);
    }
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
    emit sig_dataUpdate();
}
