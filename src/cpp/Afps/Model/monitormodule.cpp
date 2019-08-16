﻿#include "monitormodule.h"
#include <QDebug>

MonitorModule::MonitorModule(QObject *parent) : QObject(parent)
{
    appendList(new ParaMonitor(QString("进样口温度"), 0x34, "℃"));
    appendList(new ParaMonitor(QString("腔体1温度"), 0x37, "℃"));
    appendList(new ParaMonitor(QString("腔体2温度"), 0x3A, "℃"));
    appendList(new ParaMonitor(QString("热解析温度"), 0x3D, "℃"));
    appendList(new ParaMonitor(QString("紫外灯1电流"), 0x04, "mA"));
    appendList(new ParaMonitor(QString("紫外灯2电流"), 0x07, "mA"));
    appendList(new ParaMonitor(QString("紫外灯3电流"), 0x0A, "mA"));
    appendList(new ParaMonitor(QString("流量"), 0x01, "mL"));
}

QQmlListProperty<ParaMonitor> MonitorModule::getList()
{
    return QQmlListProperty<ParaMonitor>(this, this,
         &MonitorModule::appendList,
         &MonitorModule::listCount,
         &MonitorModule::get,
         &MonitorModule::clearList);
}

void MonitorModule::appendList(ParaMonitor* model)
{
    list.append(model);
}

int MonitorModule::listCount() const
{
    return list.size();
}

ParaMonitor* MonitorModule::get(int id) const
{
    return list.at(id);
}

void MonitorModule::clearList()
{
    list.clear();
}

QList<ParaMonitor* >* MonitorModule::getRawList()
{
    return &list;
}

void MonitorModule::slot_serialPortState(bool isOpen)
{
    qDebug() << TAG << "slot_serialPortState " << isOpen;
    foreach(ParaMonitor* each, list){
        each->ctrl(isOpen);
    }
}

void MonitorModule::appendList(QQmlListProperty<ParaMonitor>* list, ParaMonitor* model)
{
    reinterpret_cast< MonitorModule* >(list->data)->appendList(model);
}

int MonitorModule::listCount(QQmlListProperty<ParaMonitor>* list)
{
    return reinterpret_cast< MonitorModule* >(list->data)->listCount();
}

ParaMonitor* MonitorModule::get(QQmlListProperty<ParaMonitor>* list, int id)
{
    return reinterpret_cast< MonitorModule* >(list->data)->get(id);
}

void MonitorModule::clearList(QQmlListProperty<ParaMonitor>* list)
{
    reinterpret_cast< MonitorModule* >(list->data)->clearList();
}
