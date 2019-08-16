#ifndef SINGLEACCUCHARTMODEL_H
#define SINGLEACCUCHARTMODEL_H

#include <QObject>
#include <QDebug>
#include "../adchartmodel.h"

/**
 * @brief 单点累加图
 */
class SingleAccuChartModel : public QObject
{
    Q_OBJECT
public:
    explicit SingleAccuChartModel(int dispSize, QObject *parent = nullptr);

private:
    int dispSize; //最大显示条数
    QVector<QPointF>* m_lineData;    //当前显示线

signals:
    void sig_data(QVector<QPointF> mData, AxisRange mAxisRange); //采集原始数据

public slots:
    void slot_receiveData(double mData); //收到数据

private:
    const QString TAG = "SingleAccuChartModel";

};

#endif // SINGLEACCUCHARTMODEL_H
