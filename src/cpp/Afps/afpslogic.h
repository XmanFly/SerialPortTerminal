#ifndef AFPSLOGIC_H
#define AFPSLOGIC_H

#include <QObject>
#include <QTime>
#include <QDateTime>
#include "../Afps/Protocol/wmvolley.h"
#include "../Afps/Protocol/u8request.h"

enum AFPS_STATE {
    UNINIT, //未初始化
    IDLE,
    WORK,
    CLOSE,
    ERR,
};

class AfpsLogic : public QObject
{
    Q_OBJECT
public:
    explicit AfpsLogic(QObject *parent = nullptr);

    bool setState(AFPS_STATE newSt);
    bool sampleCtrl(bool isStart, QStringList para); //采集控制请求
    QString genFileName(const QStringList& para);

private:
    AFPS_STATE state;
    bool sampleCtrl(bool isOn); //采集控制

signals:
    void sig_sampleCtrl(bool isStart, QString fileName); //采集控制


public slots:
    void slot_serialPortState(bool isOpen); //串口状态
};

#endif // AFPSLOGIC_H
