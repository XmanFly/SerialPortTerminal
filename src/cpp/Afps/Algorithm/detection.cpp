#include "detection.h"

Detection::Detection(Para mPara, QObject *parent) :
    QObject(parent),
    points(0),
    isDectected(false),
    isTimeout(false),
    mPara(mPara)
{

}

void Detection::init()
{
    points = 0;
    isDectected = false;
    isTimeout = false;
}

//物质判定
void Detection::process(double data)
{
    points++;
    if(data < mPara.standard) {
        //下降比例
        double fallRate = (mPara.standard - data) / mPara.standard;
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



