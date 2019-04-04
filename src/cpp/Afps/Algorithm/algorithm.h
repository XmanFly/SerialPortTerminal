#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QDebug>
#include <QPointF>
#include <QVector>
#include "../adchanneldev.h"
#include "baseline.h"
#include "detection.h"

class Algorithm : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm(Baseline *mBaseline, Detection *mDetection, QObject *parent = nullptr);

    enum STATE {
        WAITE_BASELINE_STABLE, //等待背景稳定
        BASELINE_UPDATE, //基线更新
        DETECTION, //物质判定
        DETECTED, //检出
        TIMEOUT, //超时
    };

    void init();
    void setEnable(bool isEnable);

    Baseline *mBaseline;
    Detection *mDetection;
    STATE mState;

private:
    void process(double data); //处理一个数据

    bool isEnable;

signals:
    void sig_result(QString res); //本次检出结果
    void sig_state(QString state); //状态

public slots:
    void slot_receiveData(AD_CHANNEDL_DATA data);
    void slot_receiveData(double data);
    void slot_receiveData(QVector<QVector<QPointF> > data); //收到一组数据
};

#endif // ALGORITHM_H
