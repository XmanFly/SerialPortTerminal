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
    connect(mSerialPortControl, &SerialPortControl::sig_receive,
            this, &Interface::slot_serialReceive);
    mSerialPortThread->start();

    periodSendInit(); //定时发送模块初始化

#if 0
    table = new TableModel(this);
    table->insertRows(0, 1, QModelIndex());
    QModelIndex index = table->index(0, 0, QModelIndex());
    table->setData(index, "kao", Qt::EditRole);
    index = table->index(0, 1, QModelIndex());
    table->setData(index, "nani", Qt::EditRole);
#endif
}

//定时发送模块初始化
void Interface::periodSendInit()
{
    mPeriodSend = new PeriodSend();
    mPeriodSendThread = new QThread();
    connect(mPeriodSendThread, &QThread::started,
        mPeriodSend, &PeriodSend::slot_init);
    connect(this, &Interface::sig_periodSendStart,
        mPeriodSend, &PeriodSend::slot_start);
    connect(this, &Interface::sig_periodSendStop,
        mPeriodSend, &PeriodSend::slot_stop);
    connect(mPeriodSend, &PeriodSend::sig_send,
        mSerialPortControl, &SerialPortControl::slot_send);
    mPeriodSendThread->start();
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

//收到串口数据
void Interface::slot_serialReceive(QByteArray data)
{
    QString curTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz");
    QString dataStr = QString(data.toHex());
    dataList.append(new DataObject(curTime, dataStr));
    emit sig_resetDataList();
    qDebug() << "Interface::slot_serialReceive " << dataStr;
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

//获取数据Model
QVariant Interface::getDataModel()
{
    return QVariant::fromValue(dataList);
}

//清空数据Model
void Interface::clearDataModel()
{
    dataList.clear();
    emit sig_resetDataList();
}

//开启周期发送
void Interface::periodSendStart(qint32 period, QString data, bool isStart)
{
    if(isStart) {
        emit sig_periodSendStart(period, QByteArray::fromHex(data.toLatin1()));
    } else {
        emit sig_periodSendStop();
    }
}
