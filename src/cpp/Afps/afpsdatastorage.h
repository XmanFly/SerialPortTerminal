#ifndef AFPSDATASTORAGE_H
#define AFPSDATASTORAGE_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QPointF>
#include "adchanneldev.h"


//数据存储模块
class AfpsDataStorage : public QObject
{
    Q_OBJECT
public:
    explicit AfpsDataStorage( QObject *parent = nullptr );

    //连续文件信息
    struct ContFileInfor
    {
        QString fileName; //文件名
        QList<QVector<QPointF> > buffer; //保存数据
        int maxSize; //数据最大条数
    };

private:
    QString fullPath; //数据文件完整路径
    QString fileName; //文件名
    QFile   *filePtr; //文件指针

    bool createFile(QFile** fp, QString fileName); //创建文件
    void addHead(QFile** fp);
    void addData(QFile** fp, AD_CHANNEDL_DATA data);
    void closeFile(QFile** fp); //关闭文件
    void saveDirInit(QString folderName); //判断存储数据文件夹是否存在,不存在则创建新的    

public slots:
    void on_ctrl(bool isStart, QString name);
    void on_addData(AD_CHANNEDL_DATA data); //保存一组数据

signals:
    void sig_creatFileFail(); //文件创建失败


};

#endif // AFPSDATASTORAGE_H
