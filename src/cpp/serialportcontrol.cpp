#include "serialportcontrol.h"
#include <QThread>

SerialPortControl::SerialPortControl(QObject *parent) : QObject(parent)
{
    mSerialPort = nullptr;
    sendScheduler = nullptr;
}

void SerialPortControl::sendSchedulerInit()
{
    /* 开启发送调度器 */
    sendScheduler = new QTimer();
    connect(sendScheduler, &QTimer::timeout,
            this, &SerialPortControl::slot_sendSchedule);
    sendScheduler->setTimerType(Qt::TimerType::PreciseTimer);
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
           mSerialPort->setReadBufferSize(1024000);
//           mSerialPort->setDataTerminalReady(true);
           /* 连接串口接收数据槽 */
           connect(mSerialPort, &QSerialPort::readyRead,
                   this, &SerialPortControl::slot_receive);
           if(sendScheduler == nullptr){
                sendSchedulerInit();
           }
            sendScheduler->start(20);
           isOpen = true;
       } else {
           mSerialPort = nullptr; //串口打开失败
           emit sig_message("串口打开失败!\r\n(1)请检查是否已被占用\r\n(2)重新刷新设备");
       }
    }
    emit sig_state(isOpen); //串口状态变更
    qDebug() << "SerialPortControl::slot_open "
             << "result " << isOpen << " thread id " << QThread::currentThread();
}

void SerialPortControl::slot_close()
{
    bool isOpen = true; //默认打开状态
    if(mSerialPort != nullptr){
        mSerialPort->close();
        sendScheduler->stop();
        isOpen = false;
    }
    emit sig_state(isOpen);
    qDebug() << "SerialPortControl::slot_close "
             << "result " << isOpen;
}

void SerialPortControl::slot_send(QByteArray data)
{
    if(mSerialPort != nullptr){
        sendBuffer.enqueue(data);
    }
}

//接收数据
void SerialPortControl::slot_receive()
{
    QByteArray readBuf;
    readBuf = mSerialPort->readAll();
    emit sig_receive(readBuf);
    emit sig_receiveCnt(readBuf.size());
    qDebug() << "SerialPortControl::slot_receive " << readBuf.toHex();
}

void SerialPortControl::slot_sendSchedule()
{
    if(mSerialPort == nullptr){
        return;
    }
    if(sendBuffer.size() > 0) {
        QByteArray data = sendBuffer.dequeue();
        qint64 size = mSerialPort->write(data);
        emit sig_sendCnt(static_cast<qint32>(size));
        emit sig_send(data);
        qDebug() << "SerialPortControl::slot_sendSchedule thread id "
                 << QThread::currentThread() << " send size " << size;
        if(size != data.length()){
            qDebug() << "SerialPortControl::slot_sendSchedule err "
                     << mSerialPort->error();
        }
        mSerialPort->flush();
    }
}

