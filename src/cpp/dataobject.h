#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>

//![0]
class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString data READ data WRITE setData NOTIFY dataChanged)
//![0]

public:
    DataObject(QObject *parent=nullptr);
    DataObject(const QString &time, const QString &data, QObject *parent=nullptr);

    QString time() const;
    void setTime(const QString &time);

    QString data() const;
    void setData(const QString &data);

signals:
    void timeChanged();
    void dataChanged();

private:
    QString m_time; //记录时间
    QString m_data; //数据
//![1]
};
//![1]

#endif // DATAOBJECT_H
