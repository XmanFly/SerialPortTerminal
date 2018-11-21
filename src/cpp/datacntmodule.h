#ifndef DATACNTMODULE_H
#define DATACNTMODULE_H

#include <QObject>
#include "datacntmodel.h"

/* 收发数据个数模块 */
class DataCntModule : public QObject
{
    Q_OBJECT
public:
    explicit DataCntModule(QObject *parent = nullptr);

    QList<QObject*>* getModel();
    DataCntModel* getRcvCnt();
    DataCntModel* getSendCnt();
    void clear(qint32 id);

signals:

public slots:

private:
    DataCntModel *mRcvCnt; //接收数据个数
    DataCntModel *mSendCnt; //发送数据个数
    QList<QObject*> dataCnt; //数据个数
};

#endif // DATACNTMODULE_H
