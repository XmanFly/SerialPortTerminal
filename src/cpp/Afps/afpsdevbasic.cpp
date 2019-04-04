#include "afpsdevbasic.h"

AfpsDevBasic::AfpsDevBasic(DEV_ID dev, QObject *parent) :
    QObject(parent),
    DevBasic<DEV_ID, AfpsFormat, AfpsProtGen > (dev)
{
    protGen = new AfpsProtGen();
}

bool AfpsDevBasic::rcvProt(AfpsFormat prot)
{
    DEV_ID dev;
    bool ok;
    prot.getDevId(dev, ok);
    if(ok && dev == this->devId){
        this->protRcv = prot;
        parse();
        qDebug() << "AfpsDevBasic::rcvProt " << this->devId;
        return true;
    }
    return false;
}


void AfpsDevBasic::slot_rcvProt(AfpsFormat prot)
{
    qDebug() << "AfpsDevBasic thread id " << QThread::currentThreadId();
    //收到本设备协议
    if(rcvProt(prot)){
        qDebug() << "AfpsDevBasic::slot_rcvProt " << "dev id " << devId;
    }
}

