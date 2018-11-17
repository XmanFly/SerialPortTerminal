#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

/* UI与设备接口层 */
class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QObject *parent = nullptr);

    Q_INVOKABLE QList<QString> refreshDev(); //刷新串口设备

private:
    QSerialPortInfo *mSerialPortInfo; //串口信息


signals:

public slots:
};

#endif // INTERFACE_H
