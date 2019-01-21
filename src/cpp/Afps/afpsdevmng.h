#ifndef AFPSDEVMNG_H
#define AFPSDEVMNG_H

#include <QObject>
#include "afpsformat.h"
#include "afpsdevbasic.h"
#include "../ProtBasic/basicdev.h"
#include "../ProtBasic/protpara.h"

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

public slots:
//    void slot_rcvProt(AfpsFormat prot); //收到数据

};

#endif // AFPSDEVMNG_H
