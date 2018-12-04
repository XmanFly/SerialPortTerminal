#include "datacntmodel.h"

DataCntModel::DataCntModel(qint32 m_id, const QString &m_name, const int m_cnt, QObject *parent)
    : QObject(parent),
      id(m_id),
      name(m_name),
      cnt(m_cnt)
{

}

qint32	DataCntModel::getId()
{
    return id;
}

qint32	DataCntModel::getCnt()
{
    return cnt;
}

void	DataCntModel::setCnt(qint32 cnt)
{
    this->cnt = cnt;
    emit sig_cntChanged();
}

void	DataCntModel::addCnt(qint32 cnt)
{
    this->cnt += cnt;
    emit sig_cntChanged();
}

QString DataCntModel::getName()
{
    return name;
}

void DataCntModel::slot_add(qint32 cnt)
{
    addCnt(cnt);
}
