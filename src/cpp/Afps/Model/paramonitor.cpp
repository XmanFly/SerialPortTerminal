#include "paramonitor.h"

ParaMonitor::ParaMonitor(QString name, uchar rgstAddr, QObject *parent) :
    QObject(parent),
    name(name),
    rgstAddr(rgstAddr),
    value(0)
{
    timer = new QTimer();
    timer->callOnTimeout(this, &ParaMonitor::slot_read);
}

float ParaMonitor::getValue() const
{
    return value;
}

void ParaMonitor::setValue(float value)
{
    this->value = value;
    emit sig_valueChanged();
}

void ParaMonitor::ctrl(bool isOn)
{
    if(isOn){
        timer->start(1000);
    } else {
        timer->stop();
    }
}

void ParaMonitor::regist()
{
    qmlRegisterType<ParaMonitor>("ParaMonitor", 1, 0, "ParaMonitor");
}

bool ParaMonitor::readTmp()
{
    bool ret = false;
    FloatRequest* request = new FloatRequest(Request::POLL_REAL, rgstAddr);
    WmVolley::instance()->getRequestQueue()->addRequest(request);
    RequestStyle::STATE st = request->getResponse();
    if(st == RequestStyle::RESPONSED){
        value = request->getReadValue();
        ret = true;
    }
    WmVolley::instance()->getRequestQueue()->removeRequest(request);
    return ret;
}

void ParaMonitor::slot_read()
{
    timer->stop();
    readTmp();
    timer->start();
}
