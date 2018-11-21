#include "datacnt.h"

DataCnt::DataCnt(QObject *parent) : QObject(parent)
{

}

DataCnt::DataCnt(qint32 m_id, const QString &m_name, const int m_cnt, QObject *parent)
    : QObject(parent),
      id(m_id),
      name(m_name),
      cnt(m_cnt)
{

}

qint32	DataCnt::getId()
{
    return id;
}

qint32	DataCnt::getCnt()
{
    return cnt;
}

void	DataCnt::setCnt(qint32 cnt)
{
    this->cnt = cnt;
    emit sig_cntChanged();
}

void	DataCnt::addCnt(qint32 cnt)
{
    this->cnt += cnt;
    emit sig_cntChanged();
}

QString DataCnt::getName()
{
    return name;
}

void DataCnt::slot_add(qint32 cnt)
{
    addCnt(cnt);
}
