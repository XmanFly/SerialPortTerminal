#include "timeout.h"

Timeout::Timeout(int mThroldTime, float period, QObject *parent) :
    QObject(parent),
    mThroldTime(mThroldTime),
    period(period),
    cnt(0)
{
    updateThroldPoints(mThroldTime);
}

void Timeout::increase()
{
    cnt++;
}

void Timeout::clear()
{
    cnt = 0;
}

bool Timeout::isTimeout()
{
    return cnt > mThroldPoints;
}

int Timeout::throldPoints() const
{
    return mThroldPoints;
}

void Timeout::updateThroldPoints(int throld)
{
    mThroldTime = throld;
    mThroldPoints = static_cast<int>(throld/period);
}

int Timeout::throldTime() const
{
    return mThroldTime;
}
