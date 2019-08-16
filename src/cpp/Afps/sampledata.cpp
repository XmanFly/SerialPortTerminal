﻿#include "sampledata.h"

SampleData::SampleData(QObject *parent) : QObject(parent)
{

}

void SampleData::slot_upload(ProtContent src)
{
    parse(src);
}

//解析协议内容
void SampleData::parse(ProtContent src)
{
    //获取控制字
    QByteArray content = src.value;
    if(content.size() != 12){
        qDebug() << TAG << "parse " << "size mismatch";
    }
    adData.channel1 = getAd(content.mid(0, 3));
    adData.channel2 = getAd(content.mid(3, 3));
    adData.channel3 = getAd(content.mid(6, 3));
    adData.channel4 = getAd(content.mid(9, 3));
    emit sig_rcvData(adData);
    qDebug() << TAG << "parse "
             << adData.channel1 << adData.channel2
             << adData.channel3 << adData.channel4;
}

uint SampleData::getAd(const QByteArray &src)
{
    if(src.size() != 3){
        return 0;
    }
    uint ret = 0;
    for(int i=0; i<src.size(); i++){
        ret |=  ((static_cast<uint>(src.at(i)) & 0xFF) << i*8);
    }
    return ret;
}