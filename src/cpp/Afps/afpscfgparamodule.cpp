#include "afpscfgparamodule.h"

AfpsCfgParaModule::AfpsCfgParaModule(QObject *parent) :
    QObject(parent)
{
}

bool AfpsCfgParaModule::loadPara()
{
    mSettings = new QSettings(fileName, QSettings::IniFormat);
    mSettings->setIniCodec(QTextCodec::codecForName("GB2312"));
    mSettings->beginGroup(QObject::tr("Parameter"));
    QVariant value;
    //编号
    numList = mSettings->value("NUMBER").toString().split(',', QString::SkipEmptyParts);
    nameList = mSettings->value("NAME").toString().split(',', QString::SkipEmptyParts);
    concentrationList = mSettings->value("CONCENTRATION").toString().split(',');
    qDebug() << "AfpsCfgParaModule::loadPara " << numList;
    return true;
}

