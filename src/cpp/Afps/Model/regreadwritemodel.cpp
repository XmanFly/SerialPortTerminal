#include "regreadwritemodel.h"

RegReadWriteModel::RegReadWriteModel(QString name, uchar addr, RW flag, ValueType valueType, QObject *parent) :
    QObject(parent),
    name(name),
    addr(addr),
    flag(flag),
    valueType(valueType)
{
    floatW = nullptr;
    floatRSet = nullptr;
    floatRReal = nullptr;
    u8W = nullptr;
    u8RSet = nullptr;
    u8RReal = nullptr;
    addContent();
}

void RegReadWriteModel::addContent()
{
    switch (valueType) {
    case FLOAT:
        if(flag & Set){
            addFloatW();
        }
        if(flag & Read_Set){
            addFloatRSet();
        }
        if(flag & Read_Real){
            addFloatRReal();
        }
        break;
    case U8:
    case BOOL:
        if(flag & Set){
            addU8W();
        }
        if(flag & Read_Set){
            addU8RSet();
        }
        if(flag & Read_Real){
            addU8RReal();
        }
        break;
    case HEX:
        break;
    }

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
