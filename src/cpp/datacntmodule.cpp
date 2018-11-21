#include "datacntmodule.h"

DataCntModule::DataCntModule(QObject *parent) : QObject(parent)
{
    mRcvCnt = new DataCnt(0, "接收", 0); //接收数据个数
    mSendCnt = new DataCnt(1, "发送", 0); //发送数据个数

    dataCnt.append(mRcvCnt);
    dataCnt.append(mSendCnt);
}

QList<QObject*>* DataCntModule::getModel()
{
    return &dataCnt;
}

DataCnt* DataCntModule::getRcvCnt()
{
    return mRcvCnt;
}

DataCnt* DataCntModule::getSendCnt()
{
    return mSendCnt;
}

void DataCntModule::clear(qint32 id)
{
    foreach(QObject* each , dataCnt){
        DataCnt* cntPtr = static_cast<DataCnt*>(each);
        if(cntPtr->getId() == id){
            cntPtr->setCnt(0);
        }
    }
}
