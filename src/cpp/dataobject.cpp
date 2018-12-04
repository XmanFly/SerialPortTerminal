#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(const QString &m_time, const QByteArray &m_raw, FormatModel::DisplayFormat format, QObject *parent)
    : QObject(parent), time(m_time), raw(m_raw)
{
    setValue(convertValue(m_raw, format));
}

QString DataObject::getTime() const
{
    return time;
}

void DataObject::setTime(const QString &time)
{
    if (this->time != time) {
        this->time = time;
        emit timeChanged();
    }
}

QString DataObject::getValue() const
{
    return value;
}

void DataObject::setValue(const QString &value)
{
    if (this->value != value) {
        this->value = value;
        emit valueChanged();
    }
}

QString DataObject::convertValue(const QByteArray &value, FormatModel::DisplayFormat format)
{
    QString curStr;
    switch (format) {
    case FormatModel::DisplayFormat::HEX:
        curStr = QString(value.toHex());
        break;
    case FormatModel::DisplayFormat::ASCII:
        curStr = QString::fromLatin1(value.data());
        break;
    }
    return curStr;

}

