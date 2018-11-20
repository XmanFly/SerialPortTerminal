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
#include "tablemodel.h"

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

    bool getSerialPortState(); //获取串口状态

private:
    QSerialPortInfo *mSerialPortInfo; //串口信息
    SerialPortPara *mSerialPortPara; //串口参数
    SerialPortParaNonQobj *mSerialPortParaNoQobj; //串口参数 非QObject
    SerialPortControl *mSerialPortControl; //串口控制类
    QThread	*mSerialPortThread; //串口线程
    bool serialState; //串口当前状态
    QList<QObject*> dataList; //数据记录
    TableModel *table; //数据model

//控制串口设备
signals:
    void sig_openSerialPort(SerialPortParaNonQobj para); //打开串口
    void sig_closeSerialPort(); //关闭串口
    void sig_sendData(QByteArray data); //发送数据

//UI交互
signals:
    void sig_serialPortState(bool isOpen); //串口状态
    void sig_message(QString msg);//消息
    void sig_resetDataList(); //通知UI复位接收数据显示

public slots:
    void slot_serialState(bool isOpen); //设置串口状态
    void slot_serialReceive(QByteArray data); //收到串口数据

};

#endif // INTERFACE_H
