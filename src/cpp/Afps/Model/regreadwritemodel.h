﻿#ifndef REGREADWRITEMODEL_H
#define REGREADWRITEMODEL_H

#include <QObject>
#include "regfloatwritevm.h"
#include "regfloatreadvm.h"
#include "regu8writevm.h"
#include "regu8readvm.h"


/* 寄存器读写model */
class RegReadWriteModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name CONSTANT)
    Q_PROPERTY(ValueType valueType MEMBER valueType CONSTANT)
    Q_PROPERTY(RegFloatWriteVM* floatW READ getFloatW CONSTANT)
    Q_PROPERTY(RegFloatReadVM* floatRSet READ getFloatRSet CONSTANT)
    Q_PROPERTY(RegFloatReadVM* floatRReal READ getFloatRReal CONSTANT)
    Q_PROPERTY(RegU8WriteVM* u8W READ getU8W CONSTANT)
    Q_PROPERTY(RegU8ReadVM* u8RSet READ getU8RSet CONSTANT)
    Q_PROPERTY(RegU8ReadVM* u8RReal READ getU8RReal CONSTANT)
public:
    //值类型
    enum ValueType {
        FLOAT,
        U8,
        BOOL,
        HEX
    };
    Q_ENUM(ValueType)
    //读写标志
    enum RWFlag {
        Set = 0x0001, //设定值
        Read_Set = 0x0002, //读取设定值
        Read_Real = 0x0004, //读取实时值
    };
    Q_DECLARE_FLAGS(RW, RWFlag)

    explicit RegReadWriteModel(QString name = "", uchar addr = 0x01, RW flag=nullptr, ValueType valueType = FLOAT, QObject *parent = nullptr);
    void addContent();

    RegFloatWriteVM *getFloatW() const;
    void addFloatW();

    RegFloatReadVM *getFloatRSet() const;
    void addFloatRSet();

    RegFloatReadVM *getFloatRReal() const;
    void addFloatRReal();

    RegU8WriteVM *getU8W() const;
    void addU8W();

    RegU8ReadVM *getU8RSet() const;
    void addU8RSet();

    RegU8ReadVM *getU8RReal() const;
    void addU8RReal();

    static void regist();

private:
    const QString TAG = "RegReadWriteModel";
    QString name;
    uchar addr;
    RW flag;
    ValueType valueType;
    RegFloatWriteVM* floatW;
    RegFloatReadVM* floatRSet;
    RegFloatReadVM* floatRReal;
    RegU8WriteVM* u8W;
    RegU8ReadVM* u8RSet;
    RegU8ReadVM* u8RReal;

signals:

public slots:
};

Q_DECLARE_OPERATORS_FOR_FLAGS(RegReadWriteModel::RW)

#endif // REGREADWRITEMODEL_H
