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
    RegReadWriteModel* pumpSpeed = new RegReadWriteModel(
                "泵速", 0x01, RegReadWriteModel::Set | RegReadWriteModel::Read_Set);
    RegReadWriteModel* pumpCtrl = new RegReadWriteModel(
                "泵控制", 0x02, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* flow = new RegReadWriteModel(
                "流量", 0x03, RegReadWriteModel::Read_Real);
    RegReadWriteModel* uv1Current = new RegReadWriteModel(
                "紫外灯1 电流", 0x04, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* uv1Ctrl = new RegReadWriteModel(
                "紫外灯1 控制", 0x05, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* uv2Current = new RegReadWriteModel(
                "紫外灯2 电流", 0x07, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* uv2Ctrl = new RegReadWriteModel(
                "紫外灯2 控制", 0x08, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* uv3Current = new RegReadWriteModel(
                "紫外灯3 电流", 0x0A, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* uv3Ctrl = new RegReadWriteModel(
                "紫外灯3 控制", 0x0B, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
//    RegReadWriteModel* FlowModel = new RegReadWriteModel(
//                "风扇风量", 0x03, RegReadWriteModel::Read_Real);

    rwList->appendRWList(pumpSpeed);
    rwList->appendRWList(pumpCtrl);
    rwList->appendRWList(flow);
    rwList->appendRWList(uv1Current);
    rwList->appendRWList(uv1Ctrl);
    rwList->appendRWList(uv2Current);
    rwList->appendRWList(uv2Ctrl);
    rwList->appendRWList(uv3Current);
    rwList->appendRWList(uv3Ctrl);
}


