#include "regfloatreadvm.h"

RegFloatReadVM::RegFloatReadVM(Request::METHOD method, uchar addr, QObject *parent) :
    RegFloatVM (method, addr, parent),
    value(0)
{

}

bool RegFloatReadVM::readSync()
{
    bool ret = false;
    if(request != nullptr){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegFloatReadVM::slot_stateChanged);
        WmVolley::instance()->getRequestQueue()->removeRequest(request);
    }
    request = new FloatRequest(method, addr);
    connect(request, &Request::sig_stateChanged,
            this, &RegFloatReadVM::slot_stateChanged);
    WmVolley::instance()->getRequestQueue()->addRequest(request);
    RequestStyle::STATE st = request->getResponse();
    if(st == RequestStyle::RESPONSED){
        setValue(request->getReadValue());
        ret = true;
    }
    WmVolley::instance()->getRequestQueue()->removeRequest(request);
    request = nullptr;
    qDebug() << TAG << "read sync " << request;
    return ret;
}

float RegFloatReadVM::getValue()
{
    return value;
}

void RegFloatReadVM::setValue(float value)
{
    this->value = value;
    emit sig_valueChanged();
}


