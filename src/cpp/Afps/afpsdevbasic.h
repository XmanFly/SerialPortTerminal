#ifndef AFPSDEVBASIC_H
#define AFPSDEVBASIC_H

#include <QObject>
#include "afpsformat.h"
#include "../ProtBasic/basicdev.h"
#include "../ProtBasic/protpara.h"

class AfpsDevBasic : public QObject, public BasicDev<DEV_ID, AfpsFormat>
{
    Q_OBJECT
public:
    explicit AfpsDevBasic(DEV_ID dev, QObject *parent = nullptr);

    bool rcvProt(AfpsFormat prot);

signals:

public slots:
    virtual void slot_rcvProt(AfpsFormat prot) = 0; //收到新协议
};

#endif // AFPSDEVBASIC_H
