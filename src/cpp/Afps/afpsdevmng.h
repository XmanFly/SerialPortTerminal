#ifndef AFPSDEVMNG_H
#define AFPSDEVMNG_H

#include <QObject>
#include "afpsformat.h"
#include "afpsdevbasic.h"

/* 设备管理 */
class AfpsDevMng : public QObject
{
    Q_OBJECT
public:
    explicit AfpsDevMng(QObject *parent = nullptr);

    void addDev(AfpsDevBasic *dev);
    void addFinish(); //设备添加就绪

private:
    QList<AfpsDevBasic *> devList;

signals:
    void sig_rcvProt(AfpsFormat prot); //内部转发数据
    void sig_sendProt(QByteArray data); //转发协议数据至外部

public slots:

};

#endif // AFPSDEVMNG_H
