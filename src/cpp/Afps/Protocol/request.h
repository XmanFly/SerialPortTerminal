﻿#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <QtGui/QGuiApplication>
#include <QEventLoop>
#include "protcontent.h"

namespace RequestNameSpace {
    Q_NAMESPACE
    enum STATE{
        READY,
        IN_PROCESS,
        RESPONSED,
        TIMEOUT,
        ERROR_ST,
    };
    Q_ENUMS(STATE)

    class Request : public QObject
    {
        Q_OBJECT
    public:
        //操作命令
        enum METHOD {
            SET = 0, //设置
            POLL_REAL = 1, //查询实时
            POLL_SET = 2, //查询设置值
        };

    public:
        Request(Request::METHOD mMethod=POLL_REAL, uchar rgstAddr=0x01, QByteArray value=nullptr, QObject *parent = nullptr);
        ~Request();

        void setTimeStamp(uchar timeStamp);
        void start(); //开始
        STATE getResponse();
        STATE getState();
        int getRetryCnt();
        ERR_TYPE getErrType(); //错误类型

    protected:
        ProtContent content; //协议内容
        STATE state; //响应
        int timeoutThrold; //超时时间 单位:ms
        QTimer* timer; //超时定时器
        int retryCnt; //当前重试次数
        int RETRY_MAX; //最大重试次数
        ERR_TYPE errType; //错误类型

        void setState(STATE state);
        CMD_TYPE method2CmdType(Request::METHOD);
        void sendSingle(); //发送一条消息
        virtual bool parseRgstValue(ProtContent response) = 0; //解析寄存器值

    signals:
        void sig_send(QByteArray data);
        void sig_stateChanged();

    public slots:
        void slot_timeout();
        void slot_receiveResponse(ProtContent response);

    };

}


#endif // REQUEST_H