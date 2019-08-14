#include "regmodulevm.h"

RegModuleVM::RegModuleVM(QObject *parent) : QObject(parent)
{
    rwList = new RegRWListVM();
    load();
}

RegRWListVM *RegModuleVM::getRwList()
{
    return rwList;
}

void RegModuleVM::load()
{
    RegReadWriteModel* PumpModel = new RegReadWriteModel("泵速", 0x01);
    PumpModel->addFloatW();
    PumpModel->addFloatRSet();
    rwList->appendRWList(PumpModel);
    RegReadWriteModel* PumpCtrl = new RegReadWriteModel("泵控制", 0x02, RegReadWriteModel::BOOL);
    PumpCtrl->addU8W();
    PumpCtrl->addU8RSet();
    rwList->appendRWList(PumpCtrl);
    RegReadWriteModel* FlowModel = new RegReadWriteModel("流量");
    FlowModel->addFloatRReal();
    rwList->appendRWList(FlowModel);
}


