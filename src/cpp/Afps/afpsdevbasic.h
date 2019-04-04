#ifndef AFPSDEVBASIC_H
#define AFPSDEVBASIC_H

#include <QObject>
#include <QThread>
#include "afpsformat.h"
#include "afpsprotpara.h"
#include "afpsprotgen.h"
#include "../ProtBasic/devbasic.h"

class AfpsDevBasic : public QObject, public DevBasic<DEV_ID, AfpsFormat, AfpsProtGen>
{
    Q_OBJECT
public:
    explicit AfpsDevBasic(DEV_ID dev, QObject *parent = nullptr);

    bool rcvProt(AfpsFormat prot);

signals:
    void sig_sendCmd(QByteArray cmd); //发送命令

public slots:
    virtual void slot_rcvProt(AfpsFormat prot); //收到新协议
};

#endif // AFPSDEVBASIC_H
