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
    if(points > mPara.windowLen) {
        //下降比例
        double fallRate = (data - mPara.standard) / mPara.standard;
        if(fallRate > mPara.throld){
            isDectected = true;
        }
    }
    //超时检测
    if(points >= mPara.timeout){
        isTimeout = true;
    }
}

