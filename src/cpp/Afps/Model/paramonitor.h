#ifndef PARAMONITOR_H
#define PARAMONITOR_H

#include <QObject>
#include <QTimer>
#include "../Protocol/wmvolley.h"
#include "../Protocol/floatrequest.h"

/**
 * @brief 参数监视器
 */
class ParaMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name CONSTANT)
    Q_PROPERTY(float value MEMBER value READ getValue WRITE setValue NOTIFY sig_valueChanged)
public:
    explicit ParaMonitor(QString name="", uchar rgstAddr=0x00, QObject *parent = nullptr);

    float getValue() const;
    void setValue(float value);
    void ctrl(bool isOn);
    static void regist();

private:
    const QString TAG = "ParaMonitor";
    QString name;
    uchar rgstAddr;
    float value;
    QTimer* timer;
    bool isReading; //正在读取中
    bool readTmp();

signals:
    void sig_valueChanged(float value);

public slots:
    void slot_read();
};

#endif // PARAMONITOR_H
