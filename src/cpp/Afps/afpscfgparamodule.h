#ifndef AFPSCFGPARAMODULE_H
#define AFPSCFGPARAMODULE_H

#include <QObject>
#include <QSettings>
#include <QTextCodec>
#include <QStringList>
#include <QDebug>

class AfpsCfgParaModule : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString fileName WRITE setFileName)
    Q_PROPERTY(QStringList numList READ getNumList CONSTANT)
    Q_PROPERTY(QStringList nameList READ getNameList CONSTANT)
    Q_PROPERTY(QStringList concentrationList READ getConcentrationList CONSTANT)
    Q_PROPERTY(bool algorithmEn MEMBER algorithmEn CONSTANT)
    Q_PROPERTY(bool flowChartEn MEMBER flowChartEn CONSTANT)

    Q_INVOKABLE void setFileName(QString fileName){
        this->fileName = fileName;
    }
    Q_INVOKABLE bool loadPara();

public:
    explicit AfpsCfgParaModule(QObject *parent = nullptr);

    QStringList getNumList() {
        return numList;
    }
    QStringList getNameList() {
        return nameList;
    }
    QStringList getConcentrationList() {
        return concentrationList;
    }

private:
    QString fileName; //配置文件名
    QSettings *mSettings; //设置参数
    QStringList numList; //编号
    QStringList nameList; //名称
    QStringList concentrationList; //浓度编号
    bool algorithmEn; //算法使能
    bool flowChartEn; //流量图使能

signals:

public slots:


};

#endif // AFPSCFGPARAMODULE_H
