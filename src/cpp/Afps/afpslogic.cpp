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
    bool ret = false;
    if(state == IDLE) {
        emit sig_sampleCtrl(isStart, genFileName(para));
        if(sampleCtrl(isStart)){
            return true;
        }
    }
    return ret;
}

QString AfpsLogic::genFileName(const QStringList& para)
{
    if(para.size() < 1){
        return "";
    }
    QString fileName;
    fileName += QString("%1").arg(para.at(0));
    foreach(QString each, para.mid(1, para.size()-1)){
        QString tmp = each;
        if(tmp.isEmpty() ||
                tmp.remove(" ").isEmpty()){
            continue;
        }
        fileName += QString("-%1").arg(each);
    }
    return fileName;
}

bool AfpsLogic::sampleCtrl(bool isOn)
{
    bool ret = false;
    Request* request = new U8Request(Request::SET, 0xA3, isOn);
    WmVolley::instance()->getRequestQueue()->addRequest(request);
    RequestStyle::STATE st = request->getResponse();
    if(st == RequestStyle::RESPONSED){
        ret = true;
    }
    WmVolley::instance()->getRequestQueue()->removeRequest(request);
    return ret;
}

void AfpsLogic::slot_serialPortState(bool isOpen)
{
    if(isOpen) {
        state = IDLE;
    } else {
        state = CLOSE;
    }
}
