#include "afpsdevmng.h"

AfpsDevMng::AfpsDevMng(QObject *parent) : QObject(parent)
{

}

void AfpsDevMng::addDev(AfpsDevBasic *dev)
{
    devList.append(dev);
}

//设备添加就绪
void AfpsDevMng::addFinish()
{
    qDebug() << "AfpsDevMng::addFinish " << devList.size();
    for(int i=0; i<devList.size(); i++) {
        connect(this, &AfpsDevMng::sig_rcvProt,
                    devList.at(i), &AfpsDevBasic::slot_rcvProt);
    }
}

