#include "afpsdummydata.h"

AfpsDummyData::AfpsDummyData(int interval, QObject *parent) :
    DummyDataBasic (interval, parent)
{
    curId = 0;
    fullCnt = 0;
    genData();
}

void AfpsDummyData::genData()
{
    QByteArray tmp;
    tmp.append(static_cast<char>(0xAA));
    tmp.append(static_cast<char>(0x10));
    tmp.append(static_cast<char>(0x51));
    tmp.append(static_cast<char>(0x1A));
    tmp.append(static_cast<char>(0x1A));
    tmp.append(static_cast<char>(0x1A));
    tmp.append(static_cast<char>(0x2A));
    tmp.append(static_cast<char>(0x2A));
    tmp.append(static_cast<char>(0x2A));
    tmp.append(static_cast<char>(0x3A));
    tmp.append(static_cast<char>(0x3A));
    tmp.append(static_cast<char>(0x3A));
    tmp.append(static_cast<char>(0x4A));
    tmp.append(static_cast<char>(0x4A));
    tmp.append(static_cast<char>(0x4A));
    tmp.append(static_cast<char>(0xAA));
    data.append(tmp);
}

void AfpsDummyData::slot_timeout()
{
    int len;
    len = QRandomGenerator::global()->bounded(16) + 1;
    if(curId+len > 16){
        len = 16 - curId;
    }
    emit sig_data(data.at(0).mid(curId, len));
    emit sig_cnt(len);
    if(curId+len >= 16){
        fullCnt++;
        qDebug() << "AfpsDummyData::slot_timeout "
                 << "full cnt " << fullCnt;
    }
    curId = (curId+len) % 16;

}
