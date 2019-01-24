#include "AfpsDataStorage.h"
#include <QTextCodec>

AfpsDataStorage::AfpsDataStorage(QObject *parent) :
    QObject(parent),
    filePtr(nullptr)
{
    saveDirInit("Data"); //判断存储数据文件夹是否存在,不存在则创建
}

//创建文件
bool AfpsDataStorage::createFile(QFile** fp, QString fileName)
{
    bool ret = false;

    (*fp) = new QFile(fullPath+"/"+fileName + ".csv");
    if ( (*fp)->open( QIODevice::ReadWrite )) {
        addHead(fp);
        ret = true;
        qDebug() << "AfpsDataStorage " << "createFile " + fileName + "success ";
    } else {
        (*fp) = nullptr;
        emit sig_creatFileFail(); //文件创建失败
        qDebug() << "AfpsDataStorage " << "createFile " + fileName + "faile ";
    }
    return ret;
}

void AfpsDataStorage::addHead(QFile** fp)
{
    if((*fp)== nullptr){
        return;
    }
    QTextStream out(*fp);
    out.setCodec(QTextCodec::codecForName("GB2312")); //中文支持
    out << QString("时间,通道1,通道2,通道3,通道4\r\n");
    out.flush();
}

void AfpsDataStorage::addData(QFile** fp, AD_CHANNEDL_DATA data)
{
    if(filePtr == nullptr){
        return;
    }
    QString writeStr = QDateTime::currentDateTime().toString("yy.MM.dd.hh:mm:ss.zzz") + "," +
            QString::number(data.channel1) + "," +
            QString::number(data.channel2) + "," +
            QString::number(data.channel3) + "," +
            QString::number(data.channel4) + "\r\n";
    QTextStream out(*fp);
    out.setCodec(QTextCodec::codecForName("GB2312")); //中文支持
    out << writeStr;
    out.flush();
}

//关闭文件
void AfpsDataStorage::closeFile(QFile** fp)
{
    if((*fp) != nullptr){
        (*fp)->close();
        (*fp) = nullptr;
    }
}

//开始存储
void AfpsDataStorage::on_ctrl(bool isStart, QString name)
{
    if(isStart) {
        createFile(&filePtr, name); //创建文件
    } else {
        closeFile(&filePtr);
    }
}

//判断存储数据文件夹是否存在,不存在则创建
void AfpsDataStorage::saveDirInit(QString folderName)
{
    fullPath = QDir::currentPath()+"/"+folderName;
    QDir dir(fullPath);
    if(!dir.exists()){
       qDebug() << "AfpsDataStorage " << fullPath << " not exist ";
       dir.mkdir(fullPath);//只创建一级子目录，即必须保证上级目录存在
    }
}

//保存一组数据
void AfpsDataStorage::on_addData(AD_CHANNEDL_DATA data)
{
    if(filePtr != nullptr){
        addData(&filePtr, data);
    }
}

