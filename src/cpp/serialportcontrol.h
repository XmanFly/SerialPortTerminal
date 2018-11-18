#ifndef SERIALPORTCONTROL_H
#define SERIALPORTCONTROL_H

#include <QObject>
#include <QSerialPort>
#include "serialportpara.h"

/* 串口控制类 */
class SerialPortControl : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortControl(QObject *parent = nullptr);


signals:

public slots:
    void open();

};

#endif // SERIALPORTCONTROL_H
