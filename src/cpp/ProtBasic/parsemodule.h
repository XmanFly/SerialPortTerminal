#ifndef PARSEMODULE_H
#define PARSEMODULE_H

#include <QObject>
#include <QByteArray>
#include "parsebasic.h"
#include "protformatbasic.h"
#include "protpara.h"

/* 协议解析模块 */
class ParseModule : public QObject
{
    Q_OBJECT
public:
    explicit ParseModule(QObject *parent = nullptr);

    void setParseIf(ParseBasic<QByteArray,  ProtFormatBasic<PROT_FIELD, QByteArray>> *mParseIf); //设置协议解析方法

private:
    QByteArray buffer; //接收数据buffer
    ParseBasic<QByteArray,  ProtFormatBasic<PROT_FIELD, QByteArray>> *mParseIf; //协议解析方法
    int msgCnt; //解出消息个数

signals:
    void sig_result(ProtFormatBasic<PROT_FIELD, QByteArray> ); //解析结果

public slots:
    void slot_receiveData(QByteArray data); //接收数据

};

#endif // PARSEMODULE_H
