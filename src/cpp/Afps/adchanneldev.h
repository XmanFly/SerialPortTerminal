#ifndef ADCHANNELDEV_H
#define ADCHANNELDEV_H

#include <QObject>
#include <QDebug>
#include "afpsdevbasic.h"

/* AD数据 */
class AdChannelDev : public AfpsDevBasic
{
    Q_OBJECT
public:
    explicit AdChannelDev(DEV_ID dev, QObject *parent = nullptr);

    bool rcvProt(AfpsFormat prot);

signals:

public slots:
    void slot_rcvProt(AfpsFormat prot); //收到新协议
};

#endif // ADCHANNELDEV_H
