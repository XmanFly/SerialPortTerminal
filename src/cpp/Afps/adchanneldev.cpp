#include "adchanneldev.h"

AdChannelDev::AdChannelDev(DEV_ID dev, QObject *parent) :
    AfpsDevBasic(dev, parent)
{

}

//解析协议内容
void AdChannelDev::parse()
{
    //获取控制字
//    char ctrl = protRcv.getInfor(PROT_FIELD::CTRL).at(0);

}

