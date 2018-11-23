#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QTime>
#include "serialportcontrol.h"
#include "serialportpara.h"
#include "serialportparanonqobj.h"
#include "dataobject.h"
#include "rcvdatamodule.h"
#include "tablemodel.h"
#include "periodsend.h"
#include "datacntmodule.h"
#include "formatmodule.h"

/* UI与设备接口层 */
class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QObject *parent = nullptr);

    Q_PROPERTY(bool serialState READ getSerialPortState NOTIFY sig_serialPortState)
    Q_PROPERTY(NOTIFY sig_message)
    Q_PROPERTY(NOTIFY sig_resetDataList)

    Q_INVOKABLE QList<QString> refreshDev(); //刷新串口设备
    Q_INVOKABLE void setSerialPortPara(SerialPortPara *mPara); //设置串口参数
    Q_INVOKABLE void switchDev(bool isOpen); //控制设备开关
    Q_INVOKABLE void sendData(QString data); //发送数据
    Q_INVOKABLE QVariant getDataModel(); //获取数据Model
    Q_INVOKABLE void clearDataModel(); //清空数据Model
    Q_INVOKABLE void periodSendStart(qint32 period, QString data, bool isStart); //开启周期发送
    Q_INVOKABLE QVariant getDataCntModel(); //获取收发数据个数
    Q_INVOKABLE QVariant getRcvFormatModel(); //获取接收数据显示格式
    Q_INVOKABLE QVariant getSendFormatModel(); //获取发送数据格式

    bool getSerialPortState(); //获取串口状态

private:
    QSerialPortInfo *mSerialPortInfo; //串口信息
    SerialPortPara *mSerialPortPara; //串口参数
    SerialPortParaNonQobj *mSerialPortParaNoQobj; //串口参数 非QObject
    SerialPortControl *mSerialPortControl; //串口控制类
    QThread	*mSerialPortThread; //串口线程
    PeriodSend *mPeriodSend; //定时发送类
    QThread	*mPeriodSendThread; //定时发送线程
    bool serialState; //串口当前状态
    RcvDataModule *mRcvDataModule; //接收数据模块
    TableModel *table; //数据model
    DataCntModule *mDataCntModule; //数据个数模块
    FormatModule *mRcvFormatModule; //接收数据显示格式模块
    FormatModule *mSendFormatModule; //发送数据显示格式模块

    void periodSendInit(); //定时发送模块初始化
    void dataCntInit(); //收发数据个数初始化
    QByteArray convertSendData(QString data, FormatModel::DisplayFormat format); //转换发送数据

//控制串口设备
signals:
    void sig_openSerialPort(SerialPortParaNonQobj para); //打开串口
    void sig_closeSerialPort(); //关闭串口
    void sig_sendData(QByteArray data); //发送数据

//定时发送模块
signals:
    void sig_periodSendStart(qint32 period, QByteArray data); //开启定时发送
    void sig_periodSendStop(); //关闭定时发送

//UI交互
signals:
    void sig_serialPortState(bool isOpen); //串口状态
    void sig_message(QString msg);//消息
    void sig_resetDataList(); //通知UI复位接收数据显示

public slots:
    void slot_serialState(bool isOpen); //设置串口状态
    void slot_serialReceive(QByteArray data); //收到串口数据
    void slot_formatChanged(FormatModel::DisplayFormat mFormat); //切换显示模式

};

#endif // INTERFACE_H
