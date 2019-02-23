#include "loaddatafile.h"

LoadDataFile::LoadDataFile(QObject *parent) : QObject(parent)
{

}

void LoadDataFile::slot_loadFile(QString name)
{
    QVector<QVector<QPointF> > data;
    QString realPath = name;
    if(parseFile(realPath, data)) {
        emit sig_sampleCtrl(true, QString(""));
        emit sig_data(data);
        emit sig_sampleCtrl(false, QString(""));

    }
    qDebug() << "LoadDataFile::slot_loadFile "
             << realPath;
}

bool LoadDataFile::parseFile(const QString &name, QVector<QVector<QPointF> > &data)
{
    QString realPath = QUrl(name).toLocalFile();
    QFile filePtr(realPath);
    if(!filePtr.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
        return false;
    }
    data.clear();
    data.resize(4);
    QTextStream in(&filePtr);
    int lineCnt = 0;
    while(!in.atEnd()){
        QString line = in.readLine();
        qDebug() << "LoadDataFile::parseFile " << line;
        lineCnt++;
        //跳过第一行数据
        if(lineCnt == 1){
            continue;
        }
        QStringList split = line.split(",");
        if(split.size() != 5){
            filePtr.close();
            qDebug() << "LoadDataFile::parseFile " << "failed " ;
            return false;
        }
        for(int i=0; i<4; i++){
            data[i].append(QPointF(lineCnt, split.at(i+1).toDouble()));
        }
    }
    filePtr.close();
    qDebug() << "LoadDataFile::parseFile " << realPath;
    return true;
}
