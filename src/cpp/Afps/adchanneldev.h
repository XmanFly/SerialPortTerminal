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

    void parse(); //解析协议内容

signals:

public slots:
};

#endif // ADCHANNELDEV_H
