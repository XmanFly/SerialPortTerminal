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
    mSerialPortControl->moveToThread(mSerialPortThread);
    mSerialPortThread->start();
    mSerialPortThread->setPriority(QThread::Priority::TimeCriticalPriority);

    mRcvFormatModule = new FormatModule(); //接收数据格式
    mSendFormatModule = new FormatModule(); //发送数据格式
    mRcvDataModule = new RcvDataModule(); //接收数据模块初始化
    connect(mRcvDataModule, &RcvDataModule::sig_reset,
            this, &Interface::sig_resetDataList);

    periodSendInit(); //定时发送模块初始化
    dataCntInit(); //收发数据个数初始化
    afpsInit(); //荧光模块初始化

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

//收发数据个数初始化
void Interface::dataCntInit()
{
    mDataCntModule = new DataCntModule();
    connect(mSerialPortControl, &SerialPortControl::sig_sendCnt,
            mDataCntModule->getSendCnt(), &DataCntModel::slot_add);
    connect(mSerialPortControl, &SerialPortControl::sig_receiveCnt,
            mDataCntModule->getRcvCnt(), &DataCntModel::slot_add);
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
//    QString dataStr = QString(data.toHex());
    mRcvDataModule->addData(new DataObject(curTime, data, mRcvFormatModule->getFormat()));
//    emit sig_resetDataList();
//    qDebug() << "Interface::slot_serialReceive " << dataStr;
}

//切换显示模式
void Interface::slot_formatChanged(FormatModel::DisplayFormat mFormat)
{
    qDebug() << "Interface::slot_formatChanged "
             << mFormat ;
}

//发送数据
void Interface::sendData(QString data)
{
    if(serialState){
        QByteArray sendData = convertSendData(data, mSendFormatModule->getFormat());
        emit sig_sendData(sendData);
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
    return QVariant::fromValue(*mRcvDataModule->getModel());
}

//获取收发数据个数
QVariant Interface::getDataCntModel()
{
    return QVariant::fromValue(*mDataCntModule->getModel());
}

//获取显示格式
QVariant Interface::getRcvFormatModel()
{
    return QVariant::fromValue(*mRcvFormatModule->getModel());
}

//获取发送数据格式
QVariant Interface::getSendFormatModel()
{
    return QVariant::fromValue(*mSendFormatModule->getModel());
}

//清空数据Model
void Interface::clearDataModel()
{
    mRcvDataModule->clear();
}

//开启周期发送
void Interface::periodSendStart(qint32 period, QString data, bool isStart)
{
    if(isStart) {
        emit sig_periodSendStart(period, convertSendData(data, mSendFormatModule->getFormat()));
    } else {
        emit sig_periodSendStop();
    }
}

//转换发送数据
QByteArray Interface::convertSendData(QString data, FormatModel::DisplayFormat format)
{
    QByteArray sendData;
    switch (format) {
        case FormatModel::DisplayFormat::HEX:
            sendData = QByteArray::fromHex(data.toLatin1());
            qDebug() << "send hex";
            break;
        case FormatModel::DisplayFormat::ASCII:
            sendData = data.toLocal8Bit();
            qDebug() << "send ascii";
            break;
    }
    return sendData;
}

void Interface::afpsInit() //初始化
{
    mAfpsParseModule = new ParseModule();
    AfpsParse *mParseIf =
            new AfpsParse();
    mAfpsParseModule->setParseIf(
                reinterpret_cast<ParseBasic<QByteArray,  ProtFormatBasic<PROT_FIELD, QByteArray>> *>(mParseIf));
    QThread *afpsTh = new QThread();
    mAfpsParseModule->moveToThread(afpsTh);
    afpsTh->start();

#if AFPS_TEST == true
    mAfpsDummyData = new AfpsDummyData(70);
    connect(mAfpsDummyData, &AfpsDummyData::sig_data,
            mAfpsParseModule, &ParseModule::slot_receiveData);
    connect(mAfpsDummyData, &AfpsDummyData::sig_data,
            this, &Interface::slot_serialReceive);
    connect(mAfpsDummyData, &AfpsDummyData::sig_cnt,
            mDataCntModule->getSendCnt(), &DataCntModel::slot_add);
#endif
}

//荧光开始
void Interface::afpsStart()
{
#if AFPS_TEST == true
    mAfpsDummyData->start();
#endif
}

//荧光停止
void Interface::afpsStop()
{
#if AFPS_TEST == true
    mAfpsDummyData->stop();
#endif
}
