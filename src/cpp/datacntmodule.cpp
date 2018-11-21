#include "datacntmodule.h"

DataCntModule::DataCntModule(QObject *parent) : QObject(parent)
{
    mRcvCnt = new DataCntModel(0, "接收", 0); //接收数据个数
    mSendCnt = new DataCntModel(1, "发送", 0); //发送数据个数

    dataCnt.append(mRcvCnt);
    dataCnt.append(mSendCnt);
}

QList<QObject*>* DataCntModule::getModel()
{
    return &dataCnt;
}

DataCntModel* DataCntModule::getRcvCnt()
{
    return mRcvCnt;
}

DataCntModel* DataCntModule::getSendCnt()
{
    return mSendCnt;
}

void DataCntModule::clear(qint32 id)
{
    foreach(QObject* each , dataCnt){
        DataCntModel* cntPtr = static_cast<DataCntModel*>(each);
        if(cntPtr->getId() == id){
            cntPtr->setCnt(0);
        }
    }
}
