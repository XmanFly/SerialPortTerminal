#include "algorithm.h"

Algorithm::Algorithm(Baseline *mBaseline, Detection *mDetection, QObject *parent) :
    QObject(parent),
    mBaseline(mBaseline),
    mDetection(mDetection),
    mState(STATE::WAITE_BASELINE_STABLE),
    isEnable(false)
{

}

void Algorithm::init()
{
    mBaseline->init();
    mDetection->init();
}

void Algorithm::setEnable(bool isEnable)
{
    this->isEnable = isEnable;
}

//处理一个数据
void Algorithm::process(double data)
{
    switch (mState) {
    case WAITE_BASELINE_STABLE:
        mBaseline->stableJudge(data);
        if(mBaseline->isStable){
            mState = BASELINE_UPDATE;
        }
        break;
    case BASELINE_UPDATE:
        mBaseline->update(data);
        if(mBaseline->isUpdateOk) {
            mState = DETECTION;
        }
        break;
    case DETECTION:
        mDetection->process(data);
        //检出物质
        if(mDetection->isDectected){
            mState = DETECTED;
        }
        //超时
        if(mDetection->isTimeout){
            mState = TIMEOUT;
        }
        break;
    case DETECTED:
        break;
    case TIMEOUT:
        break;
    }
}

void Algorithm::slot_receiveData(AD_CHANNEDL_DATA data)
{
    if(!isEnable) return;
    double dataInUse = data.channel1;
    process(dataInUse);
    if(mState == DETECTED){
        emit sig_result("DETECTED");
    } else if(mState == TIMEOUT) {
        emit sig_result("TIMEOUT");
    }
}
