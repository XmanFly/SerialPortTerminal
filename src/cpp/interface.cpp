#include "interface.h"

Interface::Interface(QObject *parent) : QObject(parent)
{
    mSerialPortInfo = new QSerialPortInfo();
    mSerialPortControl = new SerialPortControl();
    mSerialPortThread = new QThread();
    connect(mSerialPortThread, &QThread::started,
            mSerialPortControl, &SerialPortControl::slot_init);
    connect(this, &Interface::sig_openSerialPort,
            mSerialPortControl, &SerialPortControl::slot_open);
    connect(this, &Interface::sig_closeSerialPort,
            mSerialPortControl, &SerialPortControl::slot_close);
    mSerialPortThread->start();
}

//刷新串口设备
QList<QString> Interface::refreshDev()
{
    QList<QSerialPortInfo> sysSerialPort = QSerialPortInfo::availablePorts();
    QList<QString > devName;
    foreach(QSerialPortInfo each , sysSerialPort){
        devName.append(each.portName());
    }
    qDebug() << "Interface::refreshDev " << sysSerialPort.size();
    return devName;
}

//设置串口参数
void Interface::setSerialPortPara(SerialPortPara *mPara)
{
    mSerialPortPara = mPara;
    mSerialPortParaNoQobj = new SerialPortParaNonQobj(*mSerialPortPara);
    qDebug() << "Interface::setSerialPortPara"
             << mSerialPortParaNoQobj->number <<  mSerialPortParaNoQobj->baudrate
             << mSerialPortParaNoQobj->databit <<  mSerialPortParaNoQobj->stopbit;
}

//控制设备开关
void Interface::switchDev(bool isOpen)
{
    if(isOpen){
        emit sig_openSerialPort(*mSerialPortParaNoQobj);
    } else {
        emit sig_closeSerialPort();
    }
}
