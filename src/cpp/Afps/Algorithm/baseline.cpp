#include "baseline.h"

Baseline::Baseline(Para mPara, QObject *parent) :
    QObject(parent),
    isStable(false),
    isUpdateOk(false),
    mPara(mPara)
{
    src = new QVector<double>();
    mLeastSquare = new LeastSquare();
}

void Baseline::init()
{
    isStable = false;
    isUpdateOk = false;
    src->clear();
}

void Baseline::calc()
{
    /* 线性拟合 */
    //拟合数据 x轴 此处从1开始
    QVector<double > x;
    for(int i=0; i<mPara.windowLen; i++){
        x.append(src->size()-mPara.windowLen-mPara.startPos+2+i);
    }
    //拟合数据 y轴
    QVector<double > y;
    for(int i=0; i<mPara.windowLen; i++){
        y.append(src[src->size()-mPara.windowLen-mPara.startPos+1+i]);
    }
    LeastSquare* mLS = new LeastSquare(x.toStdVector(), y.toStdVector());
    //计算拟合方差
    int sum=0;
    for(int i=0; i<x.size(); i++){
        sum += pow((y[i] - mLS->getY(x[i])), 2);
    }
    offset = sqrt(sum/x.size());
}

void Baseline::stableJudge(double data)
{
    src->append(data);
    if(src->size() < (mPara.startPos + mPara.windowLen -1)){
        return;
    }
    //线性拟合
    calc();
    //计算阈值
    if (offset <= mPara.stableThrold){
        isStable = true;
        standard = data; //更新基准值
    }
}

void Baseline::update(double data)
{
    src->append(data);
    //备份之前基准值
    double standardBk = standard;
    //线性拟合
    calc();
    //计算阈值
    if (offset <= mPara.stableThrold){
        standard = data; //更新基准值
    } else {
        standard = standardBk;
        isUpdateOk = true;
    }
}
