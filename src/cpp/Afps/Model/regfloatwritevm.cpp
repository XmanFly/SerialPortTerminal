#include "regfloatwritevm.h"

RegFloatWriteVM::RegFloatWriteVM(Request::METHOD method, uchar addr, QObject *parent) :
    RegFloatVM (method, addr, parent)
{
}

bool RegFloatWriteVM::writeSync(float value)
{
    if(request != nullptr){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegFloatWriteVM::slot_stateChanged);
        WmVolley::instance()->getRequestQueue()->removeRequest(request);
    }
    request = new FloatRequest(method, addr, value);
    WmVolley::instance()->getRequestQueue()->addRequest(request);
    connect(request, &Request::sig_stateChanged,
            this, &RegFloatWriteVM::slot_stateChanged);
    STATE st = request->getResponse();
    if(st == RESPONSED){
        return true;
    }
    return false;
}

