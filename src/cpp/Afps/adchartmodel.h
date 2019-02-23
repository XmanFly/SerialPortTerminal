#ifndef ADCHARTMODEL_H
#define ADCHARTMODEL_H

#include <QObject>
#include <QDebug>
#include <QPointF>
#include "adchanneldev.h"

class AdChartModel : public QObject
{
    Q_OBJECT
public:
    explicit AdChartModel(QObject *parent = nullptr);

    QVector<QVector<QPointF> *> channel; //通道数值
    QVector<QVector<double >> channelRange; //每个通道数值范围
    void clear();

private:
    bool isWork;
    void calcRange(); //计算每个通道数值范围

signals:
    void sig_dataUpdate();

public slots:    
    void slot_ctrl(bool isStart);
    void slot_rcvData(AD_CHANNEDL_DATA data);
    void slot_rcvAllData(QVector<QVector<QPointF> > data); //收到单次采样所有数据
};

#endif // ADCHARTMODEL_H
