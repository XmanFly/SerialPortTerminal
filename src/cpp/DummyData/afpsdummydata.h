#ifndef AFPSDUMMYDATA_H
#define AFPSDUMMYDATA_H

#include "dummydatabasic.h"
#include <QRandomGenerator>

class AfpsDummyData : public DummyDataBasic
{
public:
    AfpsDummyData(int interval, QObject *parent = nullptr);
    void genData();

private:
    int curId; //当前发送Id
    int fullCnt; //完整消息个数

public slots:
    void slot_timeout();

};

#endif // AFPSDUMMYDATA_H
