#ifndef AFPSMODULE_H
#define AFPSMODULE_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "afpsdevmng.h"
#include "adchanneldev.h"
#include "../ProtBasic/parsemodule.h"
#include "../Afps/afpsdbgswitch.h"
#include "../Afps/afpsparse.h"
#include "../DummyData/afpsdummydata.h"

class AfpsModule : public QObject
{
    Q_OBJECT
public:
    explicit AfpsModule(QObject *parent = nullptr);

    ParseModule *mAfpsParseModule; //协议解析模块
    AfpsDevMng *mAfpsDevMng; //设备管理模块

    AdChannelDev *mAdChannelDev;

signals:

public slots:
};

#endif // AFPSMODULE_H
