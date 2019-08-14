#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include <QAtomicInt>
#include "request.h"
#include "parseth.h"
#include "../../rawlog.h"
#include "../../serialportcontrol.h"

/* 消息队列 */
class RequestQueue : public QObject
{
    Q_OBJECT
public:
    RequestQueue(ParseTh* parseTh, QObject *parent = nullptr);
    RequestQueue(SerialPortControl* serial, ParseTh* parseTh, QObject *parent = nullptr);
    ~RequestQueue();

    void setSerial(SerialPortControl* serial);
    void setRawLog(RawLog *value);
    Request* addRequest(Request* req);
    void removeRequest(Request* );

signals:

public slots:

private:
    const QString TAG = "RequestQueue";
    QList<Request* >* requestQueue; //请求队列
    QAtomicInt* timeStampCreater; //时间戳生成器
    QMutex* mutex;
    SerialPortControl* serial; //串口
    ParseTh* parseTh; //解析模块
    RawLog* rawLog;
};


#endif // REQUESTQUEUE_H
