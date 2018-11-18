#ifndef SERIALPORTPARANONQOBJ_H
#define SERIALPORTPARANONQOBJ_H

#include <QSerialPort>
#include <QString>
#include "serialportpara.h"

/* 非继承自QObject 主要用来在线程间传递信息 */
class SerialPortParaNonQobj
{
public:
    SerialPortParaNonQobj();
    SerialPortParaNonQobj(SerialPortPara &mSerialPortPara);

    QString number; //串口号
    QSerialPort::BaudRate	baudrate; //波特率
    QSerialPort::DataBits	databit; //数据位
    QSerialPort::StopBits	stopbit; //停止位
};

#endif // SERIALPORTPARANONQOBJ_H
