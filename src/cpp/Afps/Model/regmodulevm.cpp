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
    /* 基本区 */
    RegReadWriteModel* pumpSpeed = new RegReadWriteModel(
                "流速", 0x01, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* pumpCtrl = new RegReadWriteModel(
                "泵控制", 0x02, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
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
    /* 温度控制区 */
    RegReadWriteModel* ctrlTmp = new RegReadWriteModel(
                "底控板温度", 0x30, RegReadWriteModel::Read_Real);
    RegReadWriteModel* innerTmp = new RegReadWriteModel(
                "内部温度", 0x31, RegReadWriteModel::Read_Real);
    RegReadWriteModel* innerHmd = new RegReadWriteModel(
                "内部湿度", 0x32, RegReadWriteModel::Read_Real, RegReadWriteModel::U8);
    RegReadWriteModel* injectTmp = new RegReadWriteModel(
                "进样口温度", 0x34, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* injectCtrl = new RegReadWriteModel(
                "进样口温度控制", 0x35, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* cav1Tmp = new RegReadWriteModel(
                "腔体1温度", 0x37, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* cav1Ctrl = new RegReadWriteModel(
                "腔体1温度控制", 0x38, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* cav2Tmp = new RegReadWriteModel(
                "腔体2温度", 0x3A, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    RegReadWriteModel* cav2Ctrl = new RegReadWriteModel(
                "腔体2温度控制", 0x3B, RegReadWriteModel::Set | RegReadWriteModel::Read_Set, RegReadWriteModel::BOOL);
    RegReadWriteModel* heatTmp = new RegReadWriteModel(
                "热解析温度", 0x3D, RegReadWriteModel::Set | RegReadWriteModel::Read_Set | RegReadWriteModel::Read_Real);
    /* 系统核心数据区 */
    RegReadWriteModel* sampleCtrl = new RegReadWriteModel(
                "采样控制", 0xA3, RegReadWriteModel::Set, RegReadWriteModel::BOOL);

    rwList->appendRWList(pumpSpeed);
    rwList->appendRWList(pumpCtrl);
    rwList->appendRWList(uv1Current);
    rwList->appendRWList(uv1Ctrl);
    rwList->appendRWList(uv2Current);
    rwList->appendRWList(uv2Ctrl);
    rwList->appendRWList(uv3Current);
    rwList->appendRWList(uv3Ctrl);
    rwList->appendRWList(ctrlTmp);
    rwList->appendRWList(innerTmp);
    rwList->appendRWList(innerHmd);
    rwList->appendRWList(injectTmp);
    rwList->appendRWList(injectCtrl);
    rwList->appendRWList(cav1Tmp);
    rwList->appendRWList(cav1Ctrl);
    rwList->appendRWList(cav2Tmp);
    rwList->appendRWList(cav2Ctrl);
    rwList->appendRWList(heatTmp);
    rwList->appendRWList(sampleCtrl);
}


