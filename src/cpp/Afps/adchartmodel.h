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

    QVector<QVector<QPointF> *> channel;
    void clear();

private:
    bool isWork;

signals:
    void sig_dataUpdate();

public slots:    
    void slot_ctrl(bool isStart);
    void slot_rcvData(AD_CHANNEDL_DATA data);
};

#endif // ADCHARTMODEL_H
