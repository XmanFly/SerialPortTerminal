#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>
#include "formatmodel.h"

//![0]
class DataObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString time READ getTime WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)

public:
    //数据类型
    enum Type {
        Receive, //接收
        Send, //发送
    };

    DataObject(const QString &m_time="", const QByteArray &m_raw=QByteArray(),
               FormatModel::DisplayFormat format=FormatModel::HEX,
               Type type = Type::Receive, QObject *parent=nullptr);

    QString getTime() const;
    void setTime(const QString &time);

    QString getValue() const;
    void setValue(const QString &value);

    QString typeStr() const;

    static QString convertValue(const QByteArray &value, FormatModel::DisplayFormat format);

signals:
    void timeChanged();
    void valueChanged();

private:
    QString time; //记录时间
    QByteArray raw; //原始数据
    Type type; //类型
    QString value; //显示字符

//![1]
};
//![1]

#endif // DATAOBJECT_H
