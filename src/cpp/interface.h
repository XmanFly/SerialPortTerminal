#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include "serialportcontrol.h"
#include "serialportpara.h"
#include "serialportparanonqobj.h"

/* UI与设备接口层 */
class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QObject *parent = nullptr);

    Q_PROPERTY(NOTIFY sig_serialPortState)

    Q_INVOKABLE QList<QString> refreshDev(); //刷新串口设备
    Q_INVOKABLE void setSerialPortPara(SerialPortPara *mPara); //设置串口参数
    Q_INVOKABLE void switchDev(bool isOpen); //控制设备开关

private:
    QSerialPortInfo *mSerialPortInfo; //串口信息
    SerialPortPara *mSerialPortPara; //串口参数
    SerialPortParaNonQobj *mSerialPortParaNoQobj; //串口参数 非QObject
    SerialPortControl *mSerialPortControl; //串口控制类
    QThread	*mSerialPortThread; //串口线程

signals:
    void sig_openSerialPort(SerialPortParaNonQobj para); //打开串口
    void sig_closeSerialPort(); //关闭串口

signals:
    void sig_serialPortState(bool isOpen); //串口状态

public slots:
};

#endif // INTERFACE_H
