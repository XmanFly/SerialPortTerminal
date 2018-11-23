#ifndef FORMATMODULE_H
#define FORMATMODULE_H

#include <QObject>
#include <QDebug>
#include "formatmodel.h"

/* 格式模块 */
class FormatModule : public QObject
{
    Q_OBJECT
public:
    explicit FormatModule(QObject *parent = nullptr);

    QList<QObject*>* getModel();
    FormatModel::DisplayFormat getFormat();

signals:

public slots:
    void slot_formatChanged(FormatModel::DisplayFormat mFormat); //格式变更

private:
    FormatModel* mHexModel; //十六进制形式
    FormatModel* mStrModel; //字符形式
    FormatModel::DisplayFormat curFormat; //当前模式
    QList<QObject*> formatList; //数据个数

};

#endif // FORMATMODULE_H
