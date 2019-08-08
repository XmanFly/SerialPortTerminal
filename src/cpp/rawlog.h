#ifndef RAWLOG_H
#define RAWLOG_H

#include <QObject>
#include <QAbstractListModel>
#include "dataobject.h"

/* 原始数据收发记录 */
class RawLog : public QAbstractListModel
{
    Q_OBJECT
public:
    enum RawLogRoles {
        Time = Qt::UserRole + 1,
        Type,
        Data,
    };

    explicit RawLog(int maxSize = 1000, QObject *parent = nullptr);
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
    void slot_receive(QByteArray );
    void slot_send(QByteArray );

private:
    const QString TAG = "RawLog";
    QVector<DataObject*> dataList; //数据列表
    int maxSize; //最大保存条数
    void addData(DataObject::Type type, QByteArray data);
};

#endif // RAWLOG_H
