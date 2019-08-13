#include "regfloatwritevm.h"
#include <QDebug>

RegFloatWriteVM::RegFloatWriteVM(Request::METHOD method, uchar addr, QObject *parent) :
    RegFloatVM (method, addr, parent)
{
}

bool RegFloatWriteVM::writeSync(float value)
{
    bool ret = false;
    if(request != nullptr){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegFloatWriteVM::slot_stateChanged);
        WmVolley::instance()->getRequestQueue()->removeRequest(request);
    }
    request = new FloatRequest(method, addr, value);
    connect(request, &Request::sig_stateChanged,
            this, &RegFloatWriteVM::slot_stateChanged);
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

