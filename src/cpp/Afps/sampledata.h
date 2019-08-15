#ifndef SAMPLEDATA_H
#define SAMPLEDATA_H

#include <QObject>
#include "adchanneldev.h"
#include "../Afps/Protocol/protcontent.h"

/* 采样数据 */
class SampleData : public QObject
{
    Q_OBJECT
public:
    explicit SampleData(QObject *parent = nullptr);
    void parse(ProtContent src); //解析协议内容
    AD_CHANNEDL_DATA adData; //AD值

private:
    const QString TAG = "SampleData";
    uint getAd(const QByteArray &src);

signals:
    void sig_rcvData(AD_CHANNEDL_DATA data);

public slots:
    void slot_upload(ProtContent ); //自主上传
};

#endif // SAMPLEDATA_H
