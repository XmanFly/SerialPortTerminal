#include "rawlogtxt.h"
#include "dataobject.h"
#include <QDateTime>
#include <QDebug>

RawLogTxt::RawLogTxt(QObject *parent) : QObject(parent)
{

}

void RawLogTxt::slot_receive(QByteArray data)
{
    addData(data, 0);
}

void RawLogTxt::slot_send(QByteArray data)
{
    addData(data, 1);
}

void RawLogTxt::addData(QByteArray src, int type)
{
    QString curTime = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh:mm:ss.zzz");
    QString typeStr;
    switch (type) {
    case 0:
        typeStr = QString("接收");
        break;
    case 1:
        typeStr = QString("发送");
        break;
    }
    QString srcStr = DataObject::convertValue(src, FormatModel::HEX);
    QString display = QString("[%1] [%2] %3 ").arg(curTime).arg(type).arg(srcStr);
    emit sig_add(display, type);
}
