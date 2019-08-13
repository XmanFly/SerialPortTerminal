#ifndef REGREADWRITEMODEL_H
#define REGREADWRITEMODEL_H

#include <QObject>
#include "../Protocol/wmvolley.h"

/* 寄存器读写model */
class RegReadWriteModel : public QObject
{
    Q_OBJECT
public:
    explicit RegReadWriteModel(QObject *parent = nullptr);

private:
    const QString TAG = "RegReadWriteModel";



signals:

public slots:
};

#endif // REGREADWRITEMODEL_H
