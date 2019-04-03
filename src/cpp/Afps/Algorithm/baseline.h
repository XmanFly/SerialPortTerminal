#ifndef BASELINE_H
#define BASELINE_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QPointF>
#include <QtMath>
#include "leastsquare.h"


/* 基线处理 */
class Baseline : public QObject
{
    Q_OBJECT
public:

    struct Para {
        int startPos; //开始检测位置 即起始忽略点数
        int windowLen; //检测窗口长度
        double stableThrold; //稳定阈值
        Para(int startPos, int windowLen, double stableThrold) {
            this->startPos = startPos;
            this->windowLen = windowLen;
            this->stableThrold = stableThrold;
        }
        Para(){
            this->startPos = 1;
            this->windowLen = 51;
            this->stableThrold = 700;
        }
    };

    explicit Baseline(Baseline::Para mPara, QObject *parent = nullptr);

    bool isStable; //基线稳定
    bool isUpdateOk; //更新完成
    double standard; //基准值
    double offset; //偏差
    Para mPara;
    QVector<double >* src; //源数据
    QVector<QPointF >* fit; //拟合后数据
    LeastSquare mLS;

    void init();
    void stableJudge(double data); //稳定判断
    void update(double data); //基线更新
    void calc();
    void updatePara(Para mPara); //更新参数

private:
    LeastSquare *mLeastSquare; //最小二乘拟合

};

#endif // BASELINE_H
