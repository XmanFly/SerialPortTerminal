#ifndef PARSETH_H
#define PARSETH_H

#include <QObject>
#include "parsefsm.h"

class ParseTh : public QObject
{
    Q_OBJECT
public:
    explicit ParseTh(QObject *parent = nullptr);
    void setParseIf(ParseFsm *mParseIf); //设置协议解析方法

private:
    const QString TAG = "ParseTh";
    QByteArray buffer; //接收数据buffer
    ParseFsm *mParseIf; //协议解析方法
    int msgCnt; //解出消息个数

signals:
    void sig_response(ProtContent ); //响应
    void sig_upload(ProtContent ); //自主上传
    void sig_err(ProtContent ); //错误

public slots:
    void slot_receiveData(QByteArray data); //接收数据
};

#endif // PARSETH_H
