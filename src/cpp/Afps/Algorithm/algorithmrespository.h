#ifndef ALGORITHMRESPOSITORY_H
#define ALGORITHMRESPOSITORY_H

#include <QObject>
#include "baseline.h"
#include "detection.h"

/* 算法参数 */
class AlgorithmRespository : public QObject
{
    Q_OBJECT
public:
    explicit AlgorithmRespository(Baseline* baseline, Detection* detection, QObject *parent = nullptr);

    Baseline::Para getBaselinePara();
    Detection::Para getDetectionPara(); //识别参数

    void setBaselinePara(Baseline::Para para);

private:
    Baseline *baseline;
    Detection *detection;
//    Baseline::Para mBaselinePara; //基线参数
//    Detection::Para mDetectionPara; //识别参数

signals:

public slots:
};

#endif // ALGORITHMRESPOSITORY_H
