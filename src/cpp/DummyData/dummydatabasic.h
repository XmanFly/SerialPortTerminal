#ifndef DUMMYDATABASIC_H
#define DUMMYDATABASIC_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QDebug>

class DummyDataBasic : public QObject
{
    Q_OBJECT
public:
    explicit DummyDataBasic(int interval, QObject *parent = nullptr);

    void start();
    void stop();
    virtual void genData() = 0;

protected:
    QVector<QByteArray > data; //模拟数据
    QTimer *timer;
    int interval;

signals:
    void sig_data(QByteArray );
    void sig_cnt(int );

public slots:
    virtual void slot_timeout() = 0;
};

#endif // DUMMYDATABASIC_H
