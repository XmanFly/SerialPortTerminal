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
    RegReadWriteModel* PumpModel = new RegReadWriteModel(
                "泵速", 0x01, RegReadWriteModel::Set | RegReadWriteModel::Read_Set);
    RegReadWriteModel* PumpCtrl = new RegReadWriteModel(
                "泵控制", 0x02, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* FlowModel = new RegReadWriteModel(
                "流量", 0x03, RegReadWriteModel::Read_Real);

    rwList->appendRWList(PumpModel);
    rwList->appendRWList(PumpCtrl);
    rwList->appendRWList(FlowModel);
}


