#ifndef RCVDATAMODULE_H
#define RCVDATAMODULE_H

#include <QObject>
#include "dataobject.h"

/* 接收数据模块 */
class RcvDataModule : public QObject
{
    Q_OBJECT
public:
    explicit RcvDataModule(QObject *parent = nullptr);

    QList<QObject*>* getModel();
    void addData(DataObject *data);
    void clear();

signals:
    void sig_reset(); //通知UI复位接收数据显示

public slots:

private:
    QList<QObject*> dataList; //数据列表

};

#endif // RCVDATAMODULE_H
