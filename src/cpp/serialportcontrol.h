#ifndef SERIALPORTCONTROL_H
#define SERIALPORTCONTROL_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
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

signals:
    void sig_state(bool isOpen);

public slots:
    void slot_init();
    void slot_open(SerialPortParaNonQobj para);
    void slot_close();

};

#endif // SERIALPORTCONTROL_H
