#ifndef DATACNTMODULE_H
#define DATACNTMODULE_H

#include <QObject>
#include "datacnt.h"

/* 收发数据个数模块 */
class DataCntModule : public QObject
{
    Q_OBJECT
public:
    explicit DataCntModule(QObject *parent = nullptr);

    QList<QObject*>* getModel();
    DataCnt* getRcvCnt();
    DataCnt* getSendCnt();
    void clear(qint32 id);

signals:

public slots:

private:
    DataCnt *mRcvCnt; //接收数据个数
    DataCnt *mSendCnt; //发送数据个数
    QList<QObject*> dataCnt; //数据个数
};

#endif // DATACNTMODULE_H
