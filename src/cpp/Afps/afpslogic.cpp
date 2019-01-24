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
bool AfpsLogic::sampleCtrl(bool isStart)
{
    Q_UNUSED(isStart)
    if(state == IDLE) {
        emit sig_sampleCtrl(isStart);
        return true;
    } else {
        return false;
    }
}

void AfpsLogic::slot_serialPortState(bool isOpen)
{
    if(isOpen) {
        state = IDLE;
    } else {
        state = CLOSE;
    }
}
