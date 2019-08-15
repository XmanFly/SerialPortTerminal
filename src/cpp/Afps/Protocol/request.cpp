#include "request.h"
#include "requestqueue.h"
#include "protutils.h"
#include <QtQml>
#include <QThread>


Request::Request(Request::METHOD mMethod, uchar rgstAddr, QByteArray value, QObject *parent) :
    QObject(parent)
{
    /* 协议内容填充 */
    sendContent.cmdType = method2CmdType(mMethod);
    sendContent.addr = rgstAddr;
    sendContent.value = value;
    /* 超时定时器 */
    timer = new QTimer();
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, &QTimer::timeout,
            this, &Request::slot_timeout);
    /* 进入就绪状态 */
    setState(RequestStyle::STATE::READY);
    retryCnt = 1;
    RETRY_MAX = 1;
    timeoutThrold = 500;
}

Request::~Request()
{
    delete timer;
}

void Request::setTimeStamp(uchar timeStamp)
{
    sendContent.timeStamp = timeStamp;
}

void Request::setState(RequestStyle::STATE state)
{
    if(this->state != state || state == RequestStyle::IN_PROCESS){
        this->state = state;
        emit sig_stateChanged();
    }
}

void Request::start()
{
    sendSingle(); //发送一条消息
    timer->start(timeoutThrold);
    setState(RequestStyle::STATE::IN_PROCESS);
}

RequestStyle::STATE Request::getResponse()
{
    qDebug() << "Request::getResponse()"
             << "thread id " << QThread::currentThread();
    while(state <= RequestStyle::IN_PROCESS){
        QCoreApplication::processEvents();
//        qDebug() << "Request::wait response" << state;
    }
    return state;
}

RequestStyle::STATE Request::getState()
{
    return state;
}

int Request::getRetryCnt()
{
    return retryCnt;
}

ERR_TYPE Request::getErrType()
{
    return errType;
}

CMD_TYPE Request::method2CmdType(Request::METHOD method)
{
    CMD_TYPE type;
    switch (method) {
    case SET:
        type = CMD_TYPE::MASTER_SET;
        break;
    case POLL_SET:
        type = CMD_TYPE::MASTER_POLL_SET;
        break;
    case POLL_REAL:
        type = CMD_TYPE::MASTER_POLL_REAL;
        break;
    }
    return type;
}

void Request::sendSingle()
{
    QByteArray raw;
    ProtUtils::contentToRaw(sendContent, raw);
    emit sig_send(raw);
}

void Request::slot_timeout()
{
    qDebug() << "Request " << "slot_timeout thread id "
                 << QThread::currentThread();
    if(retryCnt < RETRY_MAX){
        sendSingle(); //发送一条消息
        retryCnt++;
        setState(RequestStyle::IN_PROCESS);
    } else {
        timer->stop();
        setState(RequestStyle::TIMEOUT);
    }
}

void Request::slot_receiveResponse(ProtContent response)
{
    qDebug() << "Request " << "receiveResponse thread id "
             << QThread::currentThread();
    //时间戳与寄存器地址保持一致
    if(sendContent.timeStamp == response.timeStamp &&
            sendContent.addr == response.addr){
        receiveContent = response;
        if(sendContent.cmdType == CMD_TYPE::MASTER_SET){
            setState(RequestStyle::RESPONSED);
            return;
        }
        if(!parseRgstValue()){
            setState(RequestStyle::ERROR_ST);
            errType = DECODE_ERR;
        } else {
            setState(RequestStyle::RESPONSED);
        }
    }
}

void Request::slot_receiveErr(ProtContent response)
{
    qDebug() << "Request " << "receiveErr ";
    //时间戳与寄存器地址保持一致
    if(sendContent.timeStamp == response.timeStamp &&
            sendContent.addr == response.addr){
        setState(RequestStyle::ERROR_ST);
        ProtUtils::parseErr(response.value, errType);
    }
}
