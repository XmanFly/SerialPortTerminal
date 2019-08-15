#ifndef SERIALPORTCONTROL_H
#define SERIALPORTCONTROL_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QTimer>
#include <QQueue>
#include "serialportpara.h"
#include "serialportparanonqobj.h"

/* 串口控制类 */
class SerialPortControl : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortControl(QObject *parent = nullptr);

private:
    QSerialPort *mSerialPort; //串口对象
    QTimer* sendScheduler; //发送调度器
    QQueue<QByteArray> sendBuffer; //发送buffer
    void sendSchedulerInit();

signals:
    void sig_state(bool isOpen); //状态返回
    void sig_message(QString msg);//消息
    void sig_receive(QByteArray data);
    void sig_sendCnt(qint32 cnt); //发送个数
    void sig_receiveCnt(qint32 cnt); //接收个数

public slots:
    void slot_init();
    void slot_open(SerialPortParaNonQobj para);
    void slot_close();
    void slot_send(QByteArray data);
    void slot_receive(); //接收数据
    void slot_sendSchedule(); //执行一次调度
};

#endif // SERIALPORTCONTROL_H
