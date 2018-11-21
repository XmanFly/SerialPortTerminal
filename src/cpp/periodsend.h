#ifndef PERIODSEND_H
#define PERIODSEND_H

#include <QObject>
#include <QTimer>
#include <QDebug>

/* 定时发送 */
class PeriodSend : public QObject
{
    Q_OBJECT
public:
    explicit PeriodSend(QObject *parent = nullptr);

private:
    QByteArray data; //数据源
    QTimer *mPeriodTimer; //周期发送定时器
    qint32 period; //周期

signals:
    void sig_send(QByteArray data); //发送数据

public slots:
    void slot_init(); //初始化
    void slot_start(qint32 period, QByteArray data); //开启定时发送
    void slot_stop(); //关闭定时发送
    void slot_timeout(); //定时时间到
};

#endif // PERIODSEND_H
