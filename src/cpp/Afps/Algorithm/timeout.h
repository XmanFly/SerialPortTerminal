#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <QObject>

/* 超时检出 */
class Timeout : public QObject
{
    Q_OBJECT
public:
    explicit Timeout(int mThroldTime, float period = 0.07f, QObject *parent = nullptr);
    void increase(); //递增
    void clear();
    bool isTimeout();
    int throldPoints() const;
    void updateThroldPoints(int throldPoints);
    int throldTime() const;

private:
    int mThroldTime; //阈值 时间(单位:S)
    int mThroldPoints; //阈值 点数
    float period; //周期
    int cnt;

signals:

public slots:
};

#endif // TIMEOUT_H
