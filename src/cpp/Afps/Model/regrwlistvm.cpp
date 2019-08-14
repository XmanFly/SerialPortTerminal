#include "regrwlistvm.h"

RegRWListVM::RegRWListVM(QObject *parent) : QObject(parent)
{

}

QQmlListProperty<RegReadWriteModel> RegRWListVM::getRWList()
{
    return QQmlListProperty<RegReadWriteModel>(this, this,
         &RegRWListVM::appendRWList,
         &RegRWListVM::rwListCount,
         &RegRWListVM::get,
         &RegRWListVM::clearRWList);
}

void RegRWListVM::appendRWList(RegReadWriteModel* model)
{
    rwList.append(model);
}

int RegRWListVM::rwListCount() const
{
    return rwList.size();
}

RegReadWriteModel* RegRWListVM::get(int id) const
{
    return rwList.at(id);
}

void RegRWListVM::clearRWList()
{
    rwList.clear();
}

QList<RegReadWriteModel* >* RegRWListVM::getRawList()
{
    return &rwList;
}

void RegRWListVM::appendRWList(QQmlListProperty<RegReadWriteModel>* list, RegReadWriteModel* model)
{
    reinterpret_cast< RegRWListVM* >(list->data)->appendRWList(model);
}

int RegRWListVM::rwListCount(QQmlListProperty<RegReadWriteModel>* list)
{
    return reinterpret_cast< RegRWListVM* >(list->data)->rwListCount();
}

RegReadWriteModel* RegRWListVM::get(QQmlListProperty<RegReadWriteModel>* list, int id)
{
    return reinterpret_cast< RegRWListVM* >(list->data)->get(id);
}

void RegRWListVM::clearRWList(QQmlListProperty<RegReadWriteModel>* list)
{
    reinterpret_cast< RegRWListVM* >(list->data)->clearRWList();
}

