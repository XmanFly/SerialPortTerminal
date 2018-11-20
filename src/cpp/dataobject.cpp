#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
{
}

DataObject::DataObject(const QString &time, const QString &data, QObject *parent)
    : QObject(parent), m_time(time), m_data(data)
{
}

QString DataObject::time() const
{
    return m_time;
}

void DataObject::setTime(const QString &time)
{
    if (time != m_time) {
        m_time = time;
        emit timeChanged();
    }
}

QString DataObject::data() const
{
    return m_data;
}

void DataObject::setData(const QString &data)
{
    if (data != m_data) {
        m_data = data;
        emit dataChanged();
    }
}
