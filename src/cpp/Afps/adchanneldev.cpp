#include "adchanneldev.h"

AdChannelDev::AdChannelDev(DEV_ID dev, QObject *parent) :
    AfpsDevBasic(dev, parent)
{

}

bool AdChannelDev::rcvProt(AfpsFormat prot)
{
    qDebug() << "AdChannelDev::rcvProt ";
    if(prot.getDevId() == DEV_ID::DEV_AD){
        this->prot = prot;
        qDebug() << "AdChannelDev::rcvProt ";
        return true;
    }
    return false;
}

void AdChannelDev::slot_rcvProt(AfpsFormat prot)
{
    //收到本设备协议
    if(rcvProt(prot)){

    }
}
