#ifndef PARSEMODULE_H
#define PARSEMODULE_H

#include <QObject>
#include <QByteArray>
#include <QThread>
#include "../Afps/afpsformat.h"
#include "../ProtBasic/parsebasic.h"

/* 协议解析模块 */
class AfpsParseModule : public QObject
{
    Q_OBJECT
public:
    explicit AfpsParseModule(QObject *parent = nullptr);

    void setParseIf(ParseBasic<QByteArray,  AfpsFormat > *mParseIf); //设置协议解析方法

private:
    QByteArray buffer; //接收数据buffer
    ParseBasic<QByteArray,  AfpsFormat > *mParseIf; //协议解析方法
    int msgCnt; //解出消息个数

signals:
    void sig_result(AfpsFormat  ); //解析结果

public slots:
    void slot_receiveData(QByteArray data); //接收数据

};

#endif // PARSEMODULE_H
