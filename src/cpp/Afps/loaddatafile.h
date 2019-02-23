#ifndef LOADDATAFILE_H
#define LOADDATAFILE_H


#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QPointF>
#include <QUrl>

class LoadDataFile : public QObject
{
    Q_OBJECT
public:
    explicit LoadDataFile(QObject *parent = nullptr);

signals:
    void sig_data(QVector<QVector<QPointF> > data);
    void sig_sampleCtrl(bool isStart, QString fileName); //采集控制 模拟开始一次采集

public slots:
    void slot_loadFile(QString name);

private:
    bool parseFile(const QString &name, QVector<QVector<QPointF> > &data);
};

#endif // LOADDATAFILE_H
