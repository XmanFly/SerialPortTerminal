#include "periodsend.h"

PeriodSend::PeriodSend(QObject *parent) : QObject(parent)
{

}

//初始化
void PeriodSend::slot_init()
{
    mPeriodTimer = new QTimer();
    connect(mPeriodTimer, &QTimer::timeout,
            this, &PeriodSend::slot_timeout);
}

//开启定时发送
void PeriodSend::slot_start(qint32 period, QByteArray data)
{
    this->data = data;
    mPeriodTimer->start(period);
    qDebug() << "PeriodSend::slot_start " << period << data.toHex();
}

//关闭定时发送
void PeriodSend::slot_stop()
{
    mPeriodTimer->stop();
}

//定时时间到
void PeriodSend::slot_timeout()
{
    emit sig_send(data);
}

