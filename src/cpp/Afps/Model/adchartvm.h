#ifndef ADCHARTVM_H
#define ADCHARTVM_H

#include <QObject>
#include <QDebug>
#include <QtCharts>
#include <QAbstractSeries>
#include <QAbstractAxis>
#include <QVector>
#include <QPointF>
#include <QtQml>
#include "../adchartmodel.h"


class AdChartVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool start MEMBER start NOTIFY sig_start)  //开始采集 主要用来清空之前数据
    Q_PROPERTY(bool update MEMBER update NOTIFY sig_updateChart)  //更新谱图数据
    Q_PROPERTY(AxisRange sampleAxisRange MEMBER sampleAxisRange)
public:
    explicit AdChartVM(QObject *parent = nullptr);

    Q_INVOKABLE void updateChart(QAbstractSeries *series, QAbstractAxis *xAxis, QAbstractAxis *yAxis);  //更新谱图
    static void registType(){
        qmlRegisterType<AdChartVM>("AdChartVM", 1, 0, "AdChartVM");
    }

signals:
    void sig_updateChart();  //更新谱图数据
    void sig_start();

public slots:
    void slot_receiveData(QVector<QPointF> mData, AxisRange mAxisRange); //收到采样数据

protected:
    const QString TAG = "AdChartVM";
    bool update; //更新谱图 用来消除仅有NOTIF时产生的warning
    QVector<QPointF> srcData; //数据源
    AxisRange sampleAxisRange; //采样数据轴范围

private:
    bool start;
};

#endif // ADCHARTVM_H
