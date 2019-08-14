#include "regu8writevm.h"

RegU8WriteVM::RegU8WriteVM(Request::METHOD method, uchar addr, QObject *parent) :
    RegRequestVM (method, addr, parent),
    request(nullptr)
{
}

bool RegU8WriteVM::writeSync(quint8 value)
{
    bool ret = false;
    if(request != nullptr){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegU8WriteVM::slot_stateChanged);
        WmVolley::instance()->getRequestQueue()->removeRequest(request);
    }
    request = new U8Request(method, addr, value);
    requestBase = request;
    connect(request, &Request::sig_stateChanged,
            this, &RegU8WriteVM::slot_stateChanged);
    WmVolley::instance()->getRequestQueue()->addRequest(request);
    RequestStyle::STATE st = request->getResponse();
    if(st == RequestStyle::RESPONSED){
        ret = true;
    }
    WmVolley::instance()->getRequestQueue()->removeRequest(request);
    request = nullptr;
    qDebug() << TAG << "write sync " << request;
    return ret;
}
