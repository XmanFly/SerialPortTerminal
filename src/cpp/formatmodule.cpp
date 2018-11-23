#include "formatmodule.h"

FormatModule::FormatModule(QObject *parent) : QObject(parent)
{
    mHexModel = new FormatModel("HEX", true, FormatModel::DisplayFormat::HEX); //十六进制形式
    mStrModel = new FormatModel("ASCII", false, FormatModel::DisplayFormat::STR); //字符形式
    formatList.append(mHexModel);
    formatList.append(mStrModel);
    foreach(QObject* each, formatList){
        FormatModel* eachModel = static_cast<FormatModel*>(each);
        connect(eachModel, &FormatModel::sig_selected,
                this, &FormatModule::slot_formatChanged);
    }
}

QList<QObject*>* FormatModule::getModel()
{
    return &formatList;
}

void FormatModule::slot_formatChanged(FormatModel::DisplayFormat mFormat)
{
    curFormat = mFormat;
    qDebug() << "FormatModule::slot_formatChanged "
             << curFormat;
}

FormatModel::DisplayFormat FormatModule::getFormat()
{
    return curFormat;
}

