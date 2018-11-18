#include "serialportcontrol.h"

SerialPortControl::SerialPortControl(QObject *parent) : QObject(parent)
{
    mSerialPort = nullptr;
}

void SerialPortControl::slot_init()
{

}

void SerialPortControl::slot_open(SerialPortParaNonQobj para)
{
    bool isOpen = false; //默认未打开状态
    mSerialPort = new QSerialPort();
    if(mSerialPort == nullptr){
        qDebug() << "SerialPortControl::open " << "QSerialPort err";
    } else {
        /* 设置串口名称 */
       mSerialPort->setPortName(para.number);
       /* 设置波特率 */
       mSerialPort->setBaudRate(para.baudrate);
       /* 设置数据位数 */
       mSerialPort->setDataBits(para.databit);
       /* 设置奇偶校验 */
       mSerialPort->setParity(QSerialPort::NoParity);
       /* 设置停止位 */
       mSerialPort->setStopBits(para.stopbit);
       /* 设置流控制 */
       mSerialPort->setFlowControl(QSerialPort::NoFlowControl);
       /* 打开串口 */
       if(mSerialPort->open(QIODevice::ReadWrite)){
           /* 设置串口缓冲区大小，这里必须设置为这么大 */
//           mSerialPort->setReadBufferSize(SerialPortOneFrameSize);
//           mSerialPort->setDataTerminalReady(true);
           /* 连接串口接收数据槽 */
//           connect(mSerialPort, SIGNAL(readyRead()),
//                   this, SLOT(on_receiveData()));
           isOpen = true;
       } else {
           mSerialPort = nullptr; //串口打开失败
       }
    }
    emit sig_state(isOpen); //串口状态变更
    qDebug() << "SerialPortControl::slot_open "
             << "result " << isOpen;
}

void SerialPortControl::slot_close()
{
    bool isClose = false; //默认打开状态
    if(mSerialPort != nullptr){
        mSerialPort->close();
        isClose = true;
    }
    emit sig_state(isClose);
}

