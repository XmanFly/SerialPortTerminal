﻿#include "interface.h"

Interface::Interface(QObject *parent) :
    QObject(parent),
    serialState(false)
{
    qDebug() << "Interface thread id " << QThread::currentThreadId();
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

//当前路径
QString Interface::getCurPath()
{
    return QDir::currentPath();
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
    mAfpsModule = new AfpsModule();
    mAfpsAdChartModel = new AdChartModel();
    mAfpsLogic = new AfpsLogic();
    mAfpsDataStorage = new AfpsDataStorage();
    mAfpsDataStorageTh = new QThread();
    mAfpsDataStorage->moveToThread(mAfpsDataStorageTh);
    mAfpsDataStorageTh->start();
    mLoadDataFile = new LoadDataFile();
    mLoadDataFileTh = new QThread();
    mLoadDataFile->moveToThread(mLoadDataFileTh);
    mLoadDataFileTh->start();
    mAfpsAlgorithmViewModel = new AfpsAlgorithmViewModel();
    mBaseline = new Baseline(Baseline::Para(1, 51, 700));
    mDetection = new Detection(Detection::Para(31, 131, 0, 0.045));
    mAfpsAlgorithmTh = new QThread();
    mAlgorithm = new Algorithm(mBaseline, mDetection);
    mAlgorithm->moveToThread(mAfpsAlgorithmTh);
    mAfpsAlgorithmTh->start();

    connect(mLoadDataFile, &LoadDataFile::sig_sampleCtrl,
            mAfpsAdChartModel, &AdChartModel::slot_ctrl);
    connect(mLoadDataFile, &LoadDataFile::sig_data,
            mAfpsAdChartModel, &AdChartModel::slot_rcvAllData);
    connect(this, &Interface::sig_loadFile,
            mLoadDataFile, &LoadDataFile::slot_loadFile);

#if AFPS_TEST == true
    mAfpsDummyData = new AfpsDummyData(70);
    connect(mAfpsDummyData, &AfpsDummyData::sig_data,
            mAfpsModule->mAfpsParseModule, &AfpsParseModule::slot_receiveData);
    connect(mAfpsDummyData, &AfpsDummyData::sig_data,
            this, &Interface::slot_serialReceive);
    connect(mAfpsDummyData, &AfpsDummyData::sig_cnt,
            mDataCntModule->getSendCnt(), &DataCntModel::slot_add);    
#endif

    connect(mSerialPortControl, &SerialPortControl::sig_receive,
        mAfpsModule->mAfpsParseModule, &AfpsParseModule::slot_receiveData);
    connect(mSerialPortControl, &SerialPortControl::sig_state,
        mAfpsLogic, &AfpsLogic::slot_serialPortState);
    connect(mAfpsModule->mAdChannelDev, &AdChannelDev::sig_rcvData,
            mAfpsAdChartModel, &AdChartModel::slot_rcvData);
    connect(mAfpsAdChartModel, &AdChartModel::sig_dataUpdate,
            this, &Interface::sig_afpsUpdateChart);
    connect(mAfpsLogic, &AfpsLogic::sig_sampleCtrl,
            mAfpsAdChartModel, &AdChartModel::slot_ctrl);
    connect(mAfpsModule->mAdChannelDev, &AdChannelDev::sig_rcvData,
            mAfpsDataStorage, &AfpsDataStorage::on_addData);
    connect(mAfpsLogic, &AfpsLogic::sig_sampleCtrl,
            mAfpsDataStorage, &AfpsDataStorage::on_ctrl);
    connect(mAfpsModule->mAdChannelDev, &AdChannelDev::sig_rcvData,
            mAlgorithm, static_cast<void(Algorithm::*)(AD_CHANNEDL_DATA)>(&Algorithm::slot_receiveData));
    connect(mAlgorithm, &Algorithm::sig_result,
            mAfpsAlgorithmViewModel, &AfpsAlgorithmViewModel::slot_updateResult);
    connect(mLoadDataFile, &LoadDataFile::sig_data,
            mAlgorithm, static_cast<void(Algorithm::*)(QVector<QVector<QPointF> > )>(&Algorithm::slot_receiveData),
            Qt::QueuedConnection);
}

//荧光开始
void Interface::afpsStart(QStringList para)
{
    qDebug() << "Interface::afpsStart " << para;
    if(mAfpsLogic->sampleCtrl(true, para)){
        mAlgorithm->setEnable(true);
        mAlgorithm->init();
    } else {
        mAlgorithm->setEnable(false);
        emit sig_message("设备未打开 禁止操作 ");
    }
#if AFPS_TEST == true
    mAfpsDummyData->start();
#endif
}

//荧光停止
void Interface::afpsStop()
{
    if(mAfpsLogic->sampleCtrl(false, QStringList())){
    } else {
        emit sig_message("设备未打开 禁止操作 ");
    }
#if AFPS_TEST == true
    mAfpsDummyData->stop();
#endif
}

//荧光更新谱图
void Interface::afpsUpdateChannelChart(int channelId, QAbstractSeries *adChannel1, QAbstractAxis *xAxis)
{
    afpsUpdateChart(adChannel1, xAxis, *mAfpsAdChartModel->channel.at(channelId));
}

void Interface::afpsUpdateChart(QAbstractSeries *series, QAbstractAxis *xAxis, QVector<QPointF> &points)
{
    QXYSeries *xySeries = static_cast<QXYSeries *>(series);
    // Use replace instead of clear + append, it's optimized for performance
    if(points.isEmpty()) {
        xySeries->clear();
        xAxis->setRange(0, 1);
        return;
    }
    xySeries->replace(points);
    xAxis->setMin(points.first().x());
    xAxis->setMax(points.last().x());
}

QVector<qreal > Interface::afpsGetDataRange(int id)
{
    QVector<qreal > ret;
    ret.append(mAfpsAdChartModel->channelRange.at(id).at(0));
    ret.append(mAfpsAdChartModel->channelRange.at(id).at(1));
    return ret;
}

bool Interface::afpsLoadFile(QString name)
{
    emit sig_loadFile(name);
    return true;
}

