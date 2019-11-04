#include "algorithm.h"

Algorithm::Algorithm(Baseline *mBaseline, Detection *mDetection, Timeout *mTimeout, QObject *parent) :
    QObject(parent),
    mBaseline(mBaseline),
    mDetection(mDetection),
    mTimeout(mTimeout),
    mState(STATE::WAITE_BASELINE_STABLE),
    isEnable(false)
{

}

void Algorithm::init()
{
    mState = WAITE_BASELINE_STABLE;
    mBaseline->init();
    mDetection->init();
    mTimeout->clear();
    emit sig_result("");
    emit sig_state("基线稳定中");
}

void Algorithm::setEnable(bool isEnable)
{
    this->isEnable = isEnable;
    qDebug() << "Algorithm::setEnable " << isEnable;
}

//处理一个数据
void Algorithm::process(double data)
{
    switch (mState) {
    case WAITE_BASELINE_STABLE:
        mBaseline->stableJudge(data);
        if(mBaseline->isStable){
            mState = BASELINE_UPDATE;
            emit sig_state("请放物质");
            qDebug() << "Algorithm::process"
                     << "move to BASELINE_UPDATE";
        }
        break;
    case BASELINE_UPDATE:
        mBaseline->update(data);
        if(mBaseline->isUpdateOk) {
            mState = DETECTION;
            mDetection->mPara.standard = mBaseline->standard;
            emit sig_state("检测物质中");
            qDebug() << "Algorithm::process"
                     << "move to DETECTION";
        }
        break;
    case DETECTION:
        mDetection->process(data);
        //检出物质
        if(mDetection->isDectected){
            mState = DETECTED;
            emit sig_state("检出可疑物");
            qDebug() << "Algorithm::process"
                     << "move to DETECTED";
        }
        //超时
//        if(mDetection->isTimeout){
//            mState = TIMEOUT;
//            emit sig_state("超时");
//            qDebug() << "Algorithm::process"
//                     << "move to TIMEOUT";
//        }
        break;
    case DETECTED:
        break;
    case TIMEOUT:
        break;
    }
    /* 超时 */
    mTimeout->increase();
    if(mTimeout->isTimeout()){
        mState = TIMEOUT;
        emit sig_state("超时");
        qDebug() << "Algorithm::process"
                 << "move to TIMEOUT";
    }
}

void Algorithm::slot_receiveData(AD_CHANNEDL_DATA data)
{
    if(!isEnable) return;
    slot_receiveData(data.channel1);
}

void Algorithm::slot_receiveData(double data)
{
    if(!isEnable) return;
    process(data);
    if(mState == DETECTED){
        emit sig_result("DETECTED");
    }
}

void Algorithm::slot_receiveData(QVector<QVector<QPointF> > data)
{
    qDebug() << "Algorithm::slot_receiveData " << "from file " << data[1].size();
    init();
    setEnable(true);
    QVector<QPointF > src = data[0];
    foreach(QPointF each , src){
        slot_receiveData(each.y());
    }
    qDebug() << "Algorithm::slot_receiveData " << "from file " << "process finished";
}
