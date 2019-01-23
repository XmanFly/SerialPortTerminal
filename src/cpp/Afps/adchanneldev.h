#ifndef ADCHANNELDEV_H
#define ADCHANNELDEV_H

#include <QObject>
#include <QDebug>
#include "afpsdevbasic.h"

struct AD_CHANNEDL_DATA {
    AD_CHANNEDL_DATA() {
        channel1 = 0;
        channel2 = 0;
        channel3 = 0;
        channel4 = 0;
    }
    AD_CHANNEDL_DATA(const AD_CHANNEDL_DATA &src) {
        channel1 = src.channel1;
        channel2 = src.channel2;
        channel3 = src.channel3;
        channel4 = src.channel4;
    }

    uint channel1;
    uint channel2;
    uint channel3;
    uint channel4;
};
Q_DECLARE_METATYPE(AD_CHANNEDL_DATA)

/* AD数据 */
class AdChannelDev : public AfpsDevBasic
{
    Q_OBJECT
public:
    explicit AdChannelDev(DEV_ID dev, QObject *parent = nullptr);

    void parse(); //解析协议内容

    AD_CHANNEDL_DATA adData; //AD值

private:
    uint getAd(const QByteArray &src);

signals:
    void sig_rcvData(AD_CHANNEDL_DATA data);

public slots:
};

#endif // ADCHANNELDEV_H
