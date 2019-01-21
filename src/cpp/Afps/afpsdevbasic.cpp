#include "afpsdevbasic.h"

AfpsDevBasic::AfpsDevBasic(DEV_ID dev, QObject *parent) :
    QObject(parent),
    BasicDev<DEV_ID, AfpsFormat > (dev)
{

}

bool AfpsDevBasic::rcvProt(AfpsFormat prot)
{
    if(prot.getDevId() == DEV_ID::DEV_AD){
        this->prot = prot;
        return true;
    }
    return false;
}
