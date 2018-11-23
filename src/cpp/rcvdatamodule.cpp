#include "rcvdatamodule.h"

RcvDataModule::RcvDataModule(QObject *parent) : QObject(parent)
{

}

QList<QObject*>* RcvDataModule::getModel()
{
    return &dataList;
}

void RcvDataModule::addData(DataObject *data)
{
    dataList.append(data);
    emit sig_reset();
}

void RcvDataModule::clear()
{
    dataList.clear();
    emit sig_reset();
}
