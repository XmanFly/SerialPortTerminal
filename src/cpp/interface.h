#ifndef INTERFACE_H
#define INTERFACE_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QTime>
#include <QtCharts>
#include <QPointF>
#include "serialportcontrol.h"
#include "serialportpara.h"
#include "serialportparanonqobj.h"
#include "dataobject.h"
#include "rcvdatamodule.h"
#include "tablemodel.h"
#include "periodsend.h"
#include "datacntmodule.h"
#include "formatmodule.h"
#include "Afps/afpsparsemodule.h"
#include "Afps/afpsdbgswitch.h"
#include "Afps/afpsparse.h"
#include "Afps/afpsmodule.h"
#include "Afps/adchartmodel.h"
#include "Afps/afpslogic.h"
#include "Afps/afpsdatastorage.h"
#include "Afps/loaddatafile.h"
#include "DummyData/afpsdummydata.h"
#include "./Afps/Algorithm/algorithmviewmodel.h"
#include "./Afps/Algorithm/algorithm.h"

/* UI与设备接口层 */
class Interface : public QObject
{
    Q_OBJECT
public:
    explicit Interface(QObject *parent = nullptr);

    Q_PROPERTY(bool serialState READ getSerialPortState NOTIFY sig_serialPortState)
    Q_PROPERTY(NOTIFY sig_message)
    Q_PROPERTY(NOTIFY sig_resetDataList)
    Q_PROPERTY(NOTIFY sig_afpsUpdateChart)
    Q_PROPERTY(QString curPath READ getCurPath CONSTANT)

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
//荧光
    Q_INVOKABLE void afpsStart(QStringList para); //荧光开始
    Q_INVOKABLE void afpsStop(); //荧光停止
    Q_INVOKABLE void afpsUpdateChannelChart(int channelId, QAbstractSeries *adChannel1, QAbstractAxis *xAxis); //荧光更新谱图
    Q_INVOKABLE QVector<qreal> afpsGetDataRange(int id);
    Q_INVOKABLE bool afpsLoadFile(QString name);

    bool getSerialPortState(); //获取串口状态
    QString getCurPath(); //当前路径
    //算法
    AfpsAlgorithmViewModel* mAfpsAlgorithmViewModel;
    Algorithm* mAlgorithm;
    Baseline* mBaseline;
    Detection* mDetection;

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
    QString curPath; //当前路径

    void periodSendInit(); //定时发送模块初始化
    void dataCntInit(); //收发数据个数初始化
    QByteArray convertSendData(QString data, FormatModel::DisplayFormat format); //转换发送数据

//荧光
private:
    AfpsModule *mAfpsModule;
    AdChartModel *mAfpsAdChartModel;
    AfpsLogic *mAfpsLogic;
    AfpsDataStorage *mAfpsDataStorage;
    QThread *mAfpsDataStorageTh;
    AfpsDummyData *mAfpsDummyData;    
    LoadDataFile *mLoadDataFile;
    QThread *mLoadDataFileTh;
    QThread *mAfpsAlgorithmTh;
    void afpsInit(); //初始化
    void afpsUpdateChart(QAbstractSeries *series, QAbstractAxis *xAxis, QVector<QPointF> &points);

signals:
    void sig_afpsUpdateChart();
    void sig_loadFile(QString name);

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
