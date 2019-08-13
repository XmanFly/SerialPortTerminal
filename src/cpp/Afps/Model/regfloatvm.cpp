#include "regfloatvm.h"

RegFloatVM::RegFloatVM(Request::METHOD method, uchar addr, QObject *parent) :
    QObject (parent),
    request(nullptr),
    method(method),
    addr(addr)
{
}

STATE RegFloatVM::getState() const
{
    if(request == nullptr){
        return READY;
    }
    return request->getState();
}

QString RegFloatVM::getDbgMsg() const
{
    QString ret;
    if(request == nullptr){
        return "";
    }
    switch (request->getState()) {
    case READY:
        ret = QString("就绪");
        break;
    case IN_PROCESS:
        ret = QString("第%1次请求").arg(request->getRetryCnt());
        break;
    case RESPONSED:
        ret = QString("成功");
        break;
    case TIMEOUT:
        ret = QString("超时");
        break;
    case ERROR_ST:
        ret = QString("错误: ");
        switch (request->getErrType()) {
        case DEV_ADDR_ERR:
            ret += QString("设备地址");
            break;
        case FUNC_CODE_ERR:
            ret += QString("功能码");
            break;
        case LEN_ERR:
            ret += QString("CRC");
            break;
        case RGST_ADD_ERR:
            ret += QString("寄存器地址");
            break;
        }
        break;
    }
    return ret;
}

void RegFloatVM::slot_stateChanged()
{
    //任务完成 取消信号连接
    if(request->getState() > IN_PROCESS){
        disconnect(request, &Request::sig_stateChanged,
                this, &RegFloatVM::slot_stateChanged);
    }
    emit sig_stateChanged();
    emit sig_dbgMsgChanged();
}
