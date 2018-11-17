#ifndef SERIALPORTCONTROL_H
#define SERIALPORTCONTROL_H

#include <QObject>
#include <QSerialPort>

/* 串口控制类 */
class SerialPortControl : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortControl(QObject *parent = nullptr);


signals:

public slots:

};

#endif // SERIALPORTCONTROL_H
