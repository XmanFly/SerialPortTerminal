#include "detection.h"

Detection::Detection(Para mPara, QObject *parent) :
    QObject(parent),
    points(0),
    isDectected(false),
    isTimeout(false),
    mPara(mPara)
{
    setDiff(0);
    setFallRate(0);
    setMaxDiff(0);
    setMaxDiffFallRate(0);
}

void Detection::setMaxDiffFallRate(double value)
{
    maxDiffFallRate = value;
    emit sig_updateMaxDiffFallRate();
}

void Detection::setMaxDiff(double value)
{
    maxDiff = value;
    emit sig_updateMaxDiff();
}

void Detection::init()
{
    points = 0;
    isDectected = false;
    isTimeout = false;
    setDiff(0);
    setFallRate(0);
    setMaxDiff(0);
    setMaxDiffFallRate(0);
}

//物质判定
void Detection::process(double data)
{
    points++;
    if(data < mPara.standard) {
        //下降比例
        setDiff(mPara.standard - data);
        setFallRate(diff / mPara.standard);
        setMaxDiff(qMax(maxDiff, diff));
        setMaxDiffFallRate(maxDiff / mPara.standard);
        if(fallRate > mPara.throld){
            isDectected = true;
        }
//        qDebug() << "Detection::process " << fallRate;
    }
    //超时检测
    if(points >= mPara.timeout){
        isTimeout = true;
    }
}


//更新参数
void Detection::updatePara(Para mPara)
{
    this->mPara = mPara;
}


void Detection::setDiff(double diff)
{
    this->diff = diff;
    emit sig_updateDiff();
}

void Detection::setFallRate(double fallRate)
{
    this->fallRate = fallRate;
    emit sig_updateFallRate();
}


