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
}

void Detection::init()
{
    points = 0;
    isDectected = false;
    isTimeout = false;
    setDiff(0);
    setFallRate(0);
}

//物质判定
void Detection::process(double data)
{
    points++;
    if(data < mPara.standard) {
        //下降比例
        setDiff(mPara.standard - data);
        setFallRate(diff / mPara.standard);
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


