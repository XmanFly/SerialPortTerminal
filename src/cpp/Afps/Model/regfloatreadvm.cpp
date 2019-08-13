#include "regfloatreadvm.h"

RegFloatReadVM::RegFloatReadVM(Request::METHOD method, uchar addr, QObject *parent) :
    RegFloatVM (method, addr, parent)
{

}

bool RegFloatReadVM::readSync()
{
    if(request != nullptr){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegFloatReadVM::slot_stateChanged);
        WmVolley::instance()->getRequestQueue()->removeRequest(request);
    }
    request = new FloatRequest(method, addr);
    WmVolley::instance()->getRequestQueue()->addRequest(request);
    connect(request, &Request::sig_stateChanged,
            this, &RegFloatReadVM::slot_stateChanged);
    RequestStyle::STATE st = request->getResponse();
    if(st == RequestStyle::RESPONSED){
        setValue(request->getReadValue());
        return true;
    }
    return false;
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


