#include "adchartmodel.h"

AdChartModel::AdChartModel(QObject *parent) : QObject(parent)
{
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
    channel.append(new QVector<QPointF>);
}

void AdChartModel::slot_clear()
{
    foreach(QVector<QPointF >* each, channel){
        each->clear();
    }
}

void AdChartModel::slot_rcvData(AD_CHANNEDL_DATA data)
{
    channel[0]->append(QPointF(channel[0]->size() + 1, data.channel1));
    channel[1]->append(QPointF(channel[1]->size() + 1, data.channel2));
    channel[2]->append(QPointF(channel[2]->size() + 1, data.channel3));
    channel[3]->append(QPointF(channel[3]->size() + 1, data.channel4));
    emit sig_dataUpdate();
}
