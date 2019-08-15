#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QCoreApplication>
#include <QtGui/QGuiApplication>
#include <QEventLoop>
#include <QtQml>
#include "protcontent.h"

class RequestStyle : public QObject
{
    Q_OBJECT
public:
    //状态
    enum STATE{
        READY,
        IN_PROCESS,
        RESPONSED,
        TIMEOUT,
        ERROR_ST,
    };
    Q_ENUMS(STATE)

    static void registType() {
        qmlRegisterType<RequestStyle>("RequestStyle", 1, 0, "RequestStyle");
    }

};

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
    Request(Request::METHOD mMethod=POLL_SET, uchar rgstAddr=0x01, QByteArray value=nullptr, QObject *parent = nullptr);
    ~Request();

    void setTimeStamp(uchar timeStamp);
    void start(); //开始
    RequestStyle::STATE getResponse();
    RequestStyle::STATE getState();
    int getRetryCnt();
    ERR_TYPE getErrType(); //错误类型
    QByteArray getRValue(); //raw

protected:
    ProtContent sendContent; //发送协议内容
    ProtContent receiveContent; //接收协议内容
    RequestStyle::STATE state; //响应
    int timeoutThrold; //超时时间 单位:ms
    QTimer* timer; //超时定时器
    int retryCnt; //当前重试次数
    int RETRY_MAX; //最大发送次数
    ERR_TYPE errType; //错误类型

    void setState(RequestStyle::STATE state);
    CMD_TYPE method2CmdType(Request::METHOD);
    void sendSingle(); //发送一条消息
    virtual bool parseRgstValue() = 0; //解析寄存器值

private:

signals:
    void sig_send(QByteArray data);
    void sig_stateChanged();

public slots:
    void slot_timeout();
    void slot_receiveResponse(ProtContent response);
    void slot_receiveErr(ProtContent response);

};

#endif // REQUEST_H
