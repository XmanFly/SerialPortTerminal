﻿#ifndef REGMODULEVM_H
#define REGMODULEVM_H

#include <QObject>
#include "regrwlistvm.h"

class RegModuleVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RegRWListVM* RWList READ getRwList CONSTANT)
public:
    explicit RegModuleVM(QObject *parent = nullptr);
    RegRWListVM* getRwList();

private:
    const QString TAG = "RegModuleVM";
    RegRWListVM* rwList;
    void load(); //加载所有寄存器

signals:

public slots:

};

#endif // REGMODULEVM_H