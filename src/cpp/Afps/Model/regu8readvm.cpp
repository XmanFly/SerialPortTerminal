#include "regu8readvm.h"

RegU8ReadVM::RegU8ReadVM(Request::METHOD method, uchar addr, QObject *parent) :
    RegRequestVM (method, addr, parent),
    request(nullptr),
    value(0)
{

}

bool RegU8ReadVM::readSync()
{
    bool ret = false;
    if(request != nullptr){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegU8ReadVM::slot_stateChanged);
        WmVolley::instance()->getRequestQueue()->removeRequest(request);
    }
    request = new U8Request(method, addr);
    requestBase = request;
    connect(request, &Request::sig_stateChanged,
            this, &RegU8ReadVM::slot_stateChanged);
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

quint8 RegU8ReadVM::getValue()
{
    return value;
}

void RegU8ReadVM::setValue(quint8 value)
{
    this->value = value;
    emit sig_valueChanged();
}
