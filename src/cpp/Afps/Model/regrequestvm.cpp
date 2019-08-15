#include "regrequestvm.h"
#include <QDebug>

RegRequestVM::RegRequestVM(Request::METHOD method, uchar addr, QObject *parent) :
    QObject (parent),
    requestBase(nullptr),
    method(method),
    addr(addr)
{
}

RequestStyle::STATE RegRequestVM::getState() const
{
    if(requestBase == nullptr){
        return RequestStyle::READY;
    }
    return requestBase->getState();
}

QString RegRequestVM::getDbgMsg() const
{
    QString ret;
    if(requestBase == nullptr){
        return "";
    }
    switch (requestBase->getState()) {
    case RequestStyle::READY:
        ret = QString("就绪");
        break;
    case RequestStyle::IN_PROCESS:
        ret = QString("第%1次请求").arg(requestBase->getRetryCnt());
        break;
    case RequestStyle::RESPONSED:
        ret = QString("成功");
        break;
    case RequestStyle::TIMEOUT:
        ret = QString("超时");
        break;
    case RequestStyle::ERROR_ST:
        ret = QString("错误");
        switch (requestBase->getErrType()) {
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
    qDebug() << "RegFloatVM::getDbgMsg" << ret;
    return ret;
}

void RegRequestVM::slot_stateChanged()
{
    //任务完成 取消信号连接
    if(requestBase->getState() > RequestStyle::IN_PROCESS){
        disconnect(requestBase, &Request::sig_stateChanged,
                this, &RegRequestVM::slot_stateChanged);
    }
    emit sig_stateChanged();
    emit sig_dbgMsgChanged();
}
