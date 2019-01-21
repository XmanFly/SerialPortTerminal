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

////收到数据
//void AfpsDevMng::slot_rcvProt(AfpsFormat prot)
//{
//    qDebug() << "AfpsDevMng::slot_rcvProt ";
////    for(int i=0; i<devList.size(); i++) {
////        devList.at(i)->rcvProt(prot);
////    }

//}
