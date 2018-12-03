#ifndef DATACNTMODEL_H
#define DATACNTMODEL_H

#include <QObject>

/* 收发数据信息 */
class DataCntModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 cnt READ getCnt WRITE setCnt NOTIFY sig_cntChanged)
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(qint32 id READ getId CONSTANT)

public:
    DataCntModel(qint32 m_id, const QString &m_name, const int m_cnt, QObject *parent = nullptr);
    DataCntModel(QObject *parent = nullptr);

    qint32	getId();
    qint32	getCnt();
    void	setCnt(qint32 cnt);
    void	addCnt(qint32 cnt);
    QString	getName();

private:
    qint32 id; //编号
    QString name; //名称
    qint32 cnt; //数据个数

signals:
    void sig_cntChanged();

public slots:
    void slot_add(qint32 cnt);
};

#endif // DATACNTMODEL_H
