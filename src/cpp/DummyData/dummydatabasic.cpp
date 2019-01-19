#include "dummydatabasic.h"

DummyDataBasic::DummyDataBasic(int interval, QObject *parent) :
    QObject(parent),
    interval(interval)
{
    timer = new QTimer();
    connect(timer, &QTimer::timeout,
            this, &DummyDataBasic::slot_timeout);
}

void DummyDataBasic::start()
{
    qDebug() << "DummyDataBasic::start";
    timer->start(interval);
}

void DummyDataBasic::stop()
{
    qDebug() << "DummyDataBasic::stop";
    timer->stop();
}
