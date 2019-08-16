#include "afpscfgparamodule.h"

AfpsCfgParaModule::AfpsCfgParaModule(QObject *parent) :
    QObject(parent)
{
}

bool AfpsCfgParaModule::loadPara()
{
    mSettings = new QSettings(fileName, QSettings::IniFormat);
    mSettings->setIniCodec(QTextCodec::codecForName("GB2312"));
    /* 列表参数 */
    mSettings->beginGroup(QObject::tr("Parameter"));
    numList = mSettings->value("NUMBER").toString().split(',', QString::SkipEmptyParts);
    nameList = mSettings->value("NAME").toString().split(',', QString::SkipEmptyParts);
    concentrationList = mSettings->value("CONCENTRATION").toString().split(',');
    mSettings->endGroup();
    /* 使能参数 */
    mSettings->beginGroup(QObject::tr("Enable"));
    algorithmEn = mSettings->value("algorithm").toBool();
    flowChartEn = mSettings->value("flowChart").toBool();
    mSettings->endGroup();

    qDebug() << "AfpsCfgParaModule::loadPara " << numList;

    return true;
}

