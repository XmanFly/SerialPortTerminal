﻿#include "request.h"
#include "protutils.h"

using namespace RequestNameSpace;

Request::Request(Request::METHOD mMethod, uchar rgstAddr, QByteArray value, QObject *parent) :
    QObject(parent)
{
    /* 协议内容填充 */
    content.cmdType = method2CmdType(mMethod);
    content.addr = rgstAddr;
    content.value = value;
    /* 超时定时器 */
    timer = new QTimer();
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, &QTimer::timeout,
            this, &Request::slot_timeout);
    /* 进入就绪状态 */
    setState(STATE::READY);
    retryCnt = 1;
}

Request::~Request()
{
    delete timer;
}

void Request::setTimeStamp(uchar timeStamp)
{
    content.timeStamp = timeStamp;
}

void Request::setState(STATE state)
{
    if(this->state != state || state == IN_PROCESS){
        this->state = state;
        emit sig_stateChanged();
    }
}

void Request::start()
{
    sendSingle(); //发送一条消息
    timer->start(timeoutThrold);
    setState(STATE::IN_PROCESS);
}

STATE Request::getResponse()
{
//    qDebug() << "Request::getResponse()"
//             << "thread id " << QThread::currentThread();
    while(state <= IN_PROCESS){
        QCoreApplication::processEvents();
//        qDebug() << "Request::wait response" << state;
    }

    return state;
}

STATE Request::getState()
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
    case POLL_REAL:
        type = CMD_TYPE::MASTER_POLL_SET;
        break;
    case POLL_SET:
        type = CMD_TYPE::MASTER_POLL_SET;
        break;
    }
    return type;
}

void Request::sendSingle()
{
    QByteArray raw;
    ProtUtils::contentToRaw(content, raw);
    emit sig_send(raw);
}

void Request::slot_timeout()
{
    if(retryCnt < RETRY_MAX){
        sendSingle(); //发送一条消息
        retryCnt++;
        setState(IN_PROCESS);
    } else {
        timer->stop();
        setState(TIMEOUT);
    }
}

void Request::slot_receiveResponse(ProtContent response)
{
    parseRgstValue(response);
}