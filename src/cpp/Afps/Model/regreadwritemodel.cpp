#include "regreadwritemodel.h"

RegReadWriteModel::RegReadWriteModel(QString name, uchar addr, ValueType valueType, QObject *parent) :
    QObject(parent),
    name(name),
    addr(addr),
    valueType(valueType)
{
    floatW = nullptr;
    floatRSet = nullptr;
    floatRReal = nullptr;
    u8W = nullptr;
    u8RSet = nullptr;
    u8RReal = nullptr;
}

RegFloatWriteVM *RegReadWriteModel::getFloatW() const
{
    return floatW;
}

void RegReadWriteModel::addFloatW()
{
    floatW = new RegFloatWriteVM(Request::SET, addr);
}

RegFloatReadVM *RegReadWriteModel::getFloatRSet() const
{
    return floatRSet;
}

void RegReadWriteModel::addFloatRSet()
{
    floatRSet = new RegFloatReadVM(Request::POLL_SET, addr);
}

RegFloatReadVM *RegReadWriteModel::getFloatRReal() const
{
    return floatRReal;
}

void RegReadWriteModel::addFloatRReal()
{
    floatRReal = new RegFloatReadVM(Request::POLL_REAL, addr);
}

RegU8WriteVM *RegReadWriteModel::getU8W() const
{
    return u8W;
}

void RegReadWriteModel::addU8W()
{
    u8W = new RegU8WriteVM(Request::SET, addr);
}

RegU8ReadVM *RegReadWriteModel::getU8RSet() const
{
    return u8RSet;
}

void RegReadWriteModel::addU8RSet()
{
    u8RSet = new RegU8ReadVM(Request::POLL_SET, addr);
}

RegU8ReadVM *RegReadWriteModel::getU8RReal() const
{
    return u8RReal;
}

void RegReadWriteModel::addU8RReal()
{
    u8RReal = new RegU8ReadVM(Request::POLL_REAL, addr);
}

void RegReadWriteModel::regist()
{
    qmlRegisterType<RegReadWriteModel>("RegReadWriteModel", 1, 0, "RegReadWriteModel");
}
