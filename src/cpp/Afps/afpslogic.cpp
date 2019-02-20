#include "afpslogic.h"

AfpsLogic::AfpsLogic(QObject *parent) :
    QObject(parent),
    state(UNINIT)
{

}


bool AfpsLogic::setState(AFPS_STATE newSt)
{
    state = newSt;
    return true;
}

//采集控制请求
bool AfpsLogic::sampleCtrl(bool isStart, QStringList para)
{
    Q_UNUSED(isStart)
    if(state == IDLE) {
        emit sig_sampleCtrl(isStart, genFileName(para));
        return true;
    } else {
        return false;
    }
}

QString AfpsLogic::genFileName(const QStringList& para)
{
    QString fileName;
    foreach(QString each, para){
        fileName += QString("%1-").arg(each);
    }
    fileName.remove(fileName.size()-1, 1);
    return fileName;
}

void AfpsLogic::slot_serialPortState(bool isOpen)
{
    if(isOpen) {
        state = IDLE;
    } else {
        state = CLOSE;
    }
}
