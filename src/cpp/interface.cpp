#include "interface.h"

Interface::Interface(QObject *parent) :
    QObject(parent),
    serialState(false)
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
    connect(this, &Interface::sig_sendData,
            mSerialPortControl, &SerialPortControl::slot_send);
    connect(mSerialPortControl, &SerialPortControl::sig_message,
            this, &Interface::sig_message);
    connect(mSerialPortControl, &SerialPortControl::sig_state,
            this, &Interface::slot_serialState);
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
    qDebug() << "serial state" << serialState;
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

//设置串口状态
void Interface::slot_serialState(bool isOpen)
{
    serialState = isOpen;
    emit sig_serialPortState(serialState);
    qDebug() << "Interface::slot_serialState " << isOpen;
}

//发送数据
void Interface::sendData(QString data)
{
    if(serialState){
        QByteArray hexFormat = QByteArray::fromHex(data.toLatin1());
        emit sig_sendData(hexFormat);
    }
}

//获取串口状态
bool Interface::getSerialPortState()
{
    qDebug() << "getSerialPortState " << serialState;
    return  serialState;
}
