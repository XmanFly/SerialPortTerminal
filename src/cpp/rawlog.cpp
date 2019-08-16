#include "rawlog.h"
#include "formatmodel.h"
#include <QDateTime>
#include <QDebug>
#include <QThread>

RawLog::RawLog(int maxSize, QObject *parent) :
    QAbstractListModel(parent),
    maxSize(maxSize)
{

}

int RawLog::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return dataList.count();
}

QVariant RawLog::data(const QModelIndex & index, int role) const
{
//    qDebug() << TAG << "data "
//             << QString("row %1 column %2 role %3").arg(index.row()).arg(index.column()).arg(role);
    if (index.row() < 0 || index.row() >= dataList.count())
        return QVariant();

    QVariant ret;
    const DataObject* each = dataList[index.row()];
    if (role == Time) {
        ret = each->getTime();
    } else if (role == Type) {
        ret = each->typeStr();
    } else if (role == Data) {
        ret = each->getValue();
    }
    return ret;
}

void RawLog::clear()
{
    if(dataList.size() == 0) {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, dataList.size()-1);
    dataList.clear();
    endRemoveRows();
}

QHash<int, QByteArray> RawLog::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(RawLogRoles::Time, QByteArrayLiteral("Time"));
    roles.insert(RawLogRoles::Type, QByteArrayLiteral("Type"));
    roles.insert(RawLogRoles::Data, QByteArrayLiteral("Data"));
    return roles;
}

void RawLog::slot_receive(QByteArray data)
{
    qDebug() << TAG << "receive thread id " << QThread::currentThread();
    addData(DataObject::Receive, data);
}

void RawLog::slot_send(QByteArray data)
{
    qDebug() << TAG << "send thread id " << QThread::currentThread();
    addData(DataObject::Send, data);
}

void RawLog::addData(DataObject::Type type, QByteArray data)
{
    if(dataList.size() == maxSize){
//        qDebug() << TAG << "addData full ";
        beginRemoveRows(QModelIndex(), 0, 0);
        dataList.removeFirst();
        endRemoveRows();
    }
    QString curTime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    dataList.append(new DataObject(curTime, data, FormatModel::HEX, type)); //TBD
    endInsertRows();
}
