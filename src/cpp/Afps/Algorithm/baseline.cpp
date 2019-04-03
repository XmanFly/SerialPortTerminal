#include "baseline.h"

Baseline::Baseline(Para mPara, QObject *parent) :
    QObject(parent),
    isStable(false),
    isUpdateOk(false),
    mPara(mPara)
{
    src = new QVector<double>();
    fit = new QVector<QPointF>();
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
    QVector<double > x(mPara.windowLen);
    for(int i=0; i<mPara.windowLen; i++){
        x[i] = src->size()-mPara.windowLen+1+i;
//        qDebug() << "Baseline::calc " << i;
    }
    //拟合数据 y轴
    QVector<double > y(mPara.windowLen);
    for(int i=0; i<mPara.windowLen; i++){
        y[i] = (*src)[src->size()-mPara.windowLen+i];
//        qDebug() << "Baseline::calc " << i << " " << src->size()-mPara.windowLen+i;
    }
    mLS = LeastSquare(x.toStdVector(), y.toStdVector());
    //计算拟合方差
    int sum=0;
    for(int i=0; i<x.size(); i++){
        sum += pow((y[i] - mLS.getY(x[i])), 2);
    }
    offset = sqrt(sum/x.size());
//    qDebug() << "Baseline::calc " << offset;
}

void Baseline::stableJudge(double data)
{
    src->append(data);
    if(src->size() < (mPara.startPos + mPara.windowLen)){
        return;
    }
    //线性拟合
    calc();
    //计算阈值
    if (offset <= mPara.stableThrold){
        isStable = true;
        standard = data; //更新基准值
//        qDebug() << "Baseline::stableJudge " << standard;
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
        //生成拟合数据
        fit->resize(mPara.windowLen);
        for(int i=0; i<mPara.windowLen; i++){
            double x = src->size()-mPara.windowLen+1+i;
            double y = (*src)[src->size()-mPara.windowLen+i];
            (*fit)[i] = QPointF(x, mLS.getY(x));
        }
        standard = fit->last().y(); //更新基准值
//        qDebug() << "Baseline::update update " << standard << src->size();
    } else {
        standard = standardBk;
        isUpdateOk = true;
//        qDebug() << "Baseline::update last " << standardBk << src->size();
    }
}


//更新参数
void Baseline::updatePara(Para mPara)
{
    qDebug() << "Baseline::updatePara " << mPara.stableThrold;
    this->mPara = mPara;
}

